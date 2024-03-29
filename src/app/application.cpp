#include "application.hpp"
#include "../cartridge/cartridge_raw.hpp"
#include "../cpu/disasm.hpp"
#include "../ui/node.hpp"
#include "SDL_audio.h"
#include "SDL_error.h"
#include <SDL2/SDL_scancode.h>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

// FIXME: Move it somewhere else
std::vector<uint8_t> readRom(const std::string &pFilename) {
  std::ifstream file(pFilename, std::ios::binary | std::ios::ate);
  if (!file) {
    throw std::runtime_error("Failed to open file");
  }

  std::streamsize fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(fileSize);

  if (!file.read(reinterpret_cast<char *>(buffer.data()), fileSize)) {
    throw std::runtime_error("Failed to read file");
  }

  return buffer;
}

// FIXME: Move it somewhere else
static const uint32_t PALETTE[] = {0xffffffff, 0xaaaaaaff, 0x555555ff,
                                   0x000000ff};

uint32_t convertColor(uint16_t value) {
  if (value & 0x8000) {
    // GB palette
    return PALETTE[value & 0x3];
  }
  // CGB palette
  int red = ((value & 0x1f) * 0xff / 0x1f) | 0;
  int green = (((value >> 5) & 0x1f) * 0xff / 0x1f) | 0;
  int blue = (((value >> 10) & 0x1f) * 0xff / 0x1f) | 0;
  return (red << 24) | (green << 16) | (blue << 8) | 0xff;
}

app::application::application(const std::string &pRomPath) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER |
               SDL_INIT_AUDIO) != 0) {
    throw std::runtime_error(SDL_GetError());
  }

  this->mWindow = SDL_CreateWindow("gb-emulator-cpp", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, 160 * 4, 144 * 4,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (this->mWindow == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }

  this->mRenderer =
      SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (this->mRenderer == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }

  SDL_AudioSpec audioSpec;
  audioSpec.freq = 32768;
  audioSpec.format = AUDIO_S16;
  audioSpec.channels = 2;
  audioSpec.samples = 2048;
  audioSpec.callback = nullptr;
  audioSpec.userdata = nullptr;

  this->mAudioDeviceId =
      SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
  if (this->mAudioDeviceId == 0) {
    throw std::runtime_error(SDL_GetError());
  }
  SDL_PauseAudioDevice(this->mAudioDeviceId, 0);

  // Create frame buffer texture
  this->mPpuTexture = std::make_unique<ppu_texture>(*this);
  this->mFontRenderer = std::make_shared<font_renderer>(*this);

  auto rom = readRom(pRomPath);
  cartridge::cartridge_info rom_info(rom);

  this->mSystem = std::make_shared<gb_system::system>(
      rom_info.supportsCGB ? gb_system::system_type::CGB
                           : gb_system::system_type::DMG);
  this->mSystem->mCartridge = rom_info.make_cartridge(rom, *(this->mSystem));
  this->mSystem->reset();

  // this->mSystem->mCpu->mBreakpoints.push_back({cpu::breakpoint::WRITE,
  // 0x8000}); this->mSystem->mCpu->mIsBreakpointsEnabled = true;
}

void app::application::handle_event(SDL_Event &event) {
  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_W:
      this->mIsTrapAcknowledged = false;
      this->mSystem->mCpu->mIsTrapped = false;
      break;
    case SDL_SCANCODE_E:
      this->mIsStepping = true;
      break;
    case SDL_SCANCODE_R:
      this->mSystem->reset();
      break;
    case SDL_SCANCODE_T:
      this->mIsStatsShown = !this->mIsStatsShown;
    default:
      break;
    }
    break;
  }
  switch (event.type) {
  case SDL_KEYDOWN:
  case SDL_KEYUP: {
    int key = -1;
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_Z:
      key = gb_system::gamepad_button::B;
      break;
    case SDL_SCANCODE_X:
      key = gb_system::gamepad_button::A;
      break;
    case SDL_SCANCODE_RETURN:
      key = gb_system::gamepad_button::START;
      break;
    case SDL_SCANCODE_BACKSPACE:
      key = gb_system::gamepad_button::SELECT;
      break;
    case SDL_SCANCODE_UP:
      key = gb_system::gamepad_button::UP;
      break;
    case SDL_SCANCODE_LEFT:
      key = gb_system::gamepad_button::LEFT;
      break;
    case SDL_SCANCODE_RIGHT:
      key = gb_system::gamepad_button::RIGHT;
      break;
    case SDL_SCANCODE_DOWN:
      key = gb_system::gamepad_button::DOWN;
      break;
    default:
      key = -1;
    }
    if (key >= 0) {
      this->mSystem->mGamepad->set(key, event.type == SDL_KEYDOWN);
    }
    break;
  }
  default:
    break;
  }
}

void app::application::update() {
  SDL_RenderClear(this->mRenderer);

  auto &system = *(this->mSystem);

  if (this->mIsStepping) {
    this->mIsTrapAcknowledged = false;
    system.mCpu->mIsTrapped = false;
  }

  // Run 1 frame
  int stopClock = system.mCpu->mClocks + 17556;
  while (system.mCpu->mClocks < stopClock) {
    if (system.mCpu->mIsTrapped) {
      break;
    }
    system.mInterrupter->step();
    if (!system.mCpu->mIsRunning) {
      system.mCpu->mClocks += 1;
      system.tick(1);
    }
    if (this->mIsStepping) {
      system.mCpu->mIsTrapped = true;
      this->mIsStepping = false;
      break;
    }
  }
  if (system.mCpu->mIsTrapped && !this->mIsTrapAcknowledged) {
    this->mIsTrapAcknowledged = true;
    std::cout << system.mCpu->debug_state()
              << std::format("; ${:04x}: ", system.mCpu->mRegister.pc)
              << cpu::opcode::disasm_op(*(system.mCpu)) << std::endl;
  }

  // Update frame buffer
  this->mPpuTexture->update();
  SDL_RenderCopy(this->mRenderer, this->mPpuTexture->mTexture, NULL, NULL);

  if (this->mIsStatsShown) {
    this->mFontRenderer->reset();
    this->mFontRenderer->write(std::format("CLK: {}\n", system.mCpu->mClocks));
    this->mFontRenderer->write(system.mCpu->debug_state());
    this->mFontRenderer->write(
        std::format("\nIME: {}\n", system.mCpu->mIsInterruptsEnabled));
    this->mFontRenderer->write(
        std::format("IE: {:02x} ", system.mInterrupter->mInterruptsEnable));
    this->mFontRenderer->write(
        std::format("IF: {:02x}\n", system.mInterrupter->mInterruptsFlag));
    this->mFontRenderer->write(
        std::format("LCDC: {:02x} ", system.mPpu->mLcdc));
    this->mFontRenderer->write(
        std::format("STAT: {:02x} ", system.mPpu->mStat));
    this->mFontRenderer->write(std::format("LY: {:02x} ", system.mPpu->mLy));
    this->mFontRenderer->write(std::format("LYC: {:02x}\n", system.mPpu->mLyc));
    this->mFontRenderer->write(
        std::format("DIV: {:02x} ", (system.mTimer->mClocks / 256) & 0xff));
    this->mFontRenderer->write(
        std::format("TIMA: {:02x} ", system.mTimer->mTima));
    this->mFontRenderer->write(
        std::format("TMA: {:02x} ", system.mTimer->mTma));
    this->mFontRenderer->write(
        std::format("TAC: {:02x}\n", system.mTimer->mTac));
  }

  // Submit audio
  auto &buf = this->mSystem->mApu->finalize();
  SDL_QueueAudio(this->mAudioDeviceId, buf.data(), buf.size() * 2);

  /*
  // An attempt at rendering the node
  {
    int winWidth;
    int winHeight;
    SDL_GetWindowSize(this->mWindow, &winWidth, &winHeight);
    auto rootEl = std::make_shared<ui::element>("DIV");
    auto boxEl = std::make_shared<ui::element>("DIV");
    auto textEl = std::make_shared<ui::text>("Hello,");
    auto bEl = std::make_shared<ui::element>("B");
    auto text2El = std::make_shared<ui::text>("world!");

    rootEl->style().padding.top = {ui::length_unit_type::PX, 10};
    rootEl->style().padding.left = {ui::length_unit_type::PX, 10};
    rootEl->style().padding.right = {ui::length_unit_type::PX, 10};
    rootEl->style().padding.bottom = {ui::length_unit_type::PX, 10};

    boxEl->style().background = {ui::color_value::RGB, {0xFFAAAA}};
    boxEl->style().padding.top = {ui::length_unit_type::PX, 10};
    boxEl->style().padding.left = {ui::length_unit_type::PX, 10};
    boxEl->style().padding.right = {ui::length_unit_type::PX, 10};
    boxEl->style().padding.bottom = {ui::length_unit_type::PX, 10};
    boxEl->style().border.top = {{ui::length_unit_type::PX, 3},
  ui::border_style::SOLID, {ui::color_value::RGB, {0x00FF00}}};
    boxEl->style().border.left = {{ui::length_unit_type::PX, 3},
  ui::border_style::SOLID, {ui::color_value::RGB, {0x00FF00}}};
    boxEl->style().border.right = {{ui::length_unit_type::PX, 3},
  ui::border_style::SOLID, {ui::color_value::RGB, {0x00FF00}}};
    boxEl->style().border.bottom = {{ui::length_unit_type::PX, 3},
  ui::border_style::SOLID, {ui::color_value::RGB, {0x00FF00}}};

    bEl->style().background = {ui::color_value::RGB, {0x0000FF}};
    bEl->style().margin.top = {ui::length_unit_type::PX, 20};
    bEl->style().padding.top = {ui::length_unit_type::PX, 5};
    bEl->style().padding.left = {ui::length_unit_type::PX, 30};
    bEl->style().padding.right = {ui::length_unit_type::PX, 30};
    bEl->style().padding.bottom = {ui::length_unit_type::PX, 5};

    rootEl->append_child(boxEl);
    boxEl->append_child(textEl);
    boxEl->append_child(bEl);
    bEl->append_child(text2El);

    ui::layout_handle layoutHandle{
        0,
        0,
        winWidth,
        0,
    };
    rootEl->layout(layoutHandle);

    ui::render_handle renderHandle{
        this->mRenderer,
        nullptr,
        &(*(this->mFontRenderer)),
    };
    rootEl->render(renderHandle);
  }
  */

  SDL_RenderPresent(this->mRenderer);
}

app::application::~application() {
  this->mSystem = nullptr;
  this->mPpuTexture = nullptr;
  this->mFontRenderer = nullptr;
  if (this->mRenderer != nullptr) {
    SDL_DestroyRenderer(this->mRenderer);
    this->mRenderer = nullptr;
  }
  if (this->mWindow != nullptr) {
    SDL_DestroyWindow(this->mWindow);
    this->mWindow = nullptr;
  }
  if (this->mAudioDeviceId == 0) {
    SDL_CloseAudioDevice(this->mAudioDeviceId);
    this->mAudioDeviceId = 0;
  }
}
