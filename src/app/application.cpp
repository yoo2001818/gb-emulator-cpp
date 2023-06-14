#include <fstream>
#include <vector>
#include <format>
#include "application.hpp"
#include "../cartridge/cartridge_raw.hpp"

// FIXME: Move it somewhere else
std::vector<uint8_t> readRom(const std::string &pFilename)
{
  std::ifstream file(pFilename, std::ios::binary | std::ios::ate);
  if (!file)
  {
    throw std::runtime_error("Failed to open file");
  }

  std::streamsize fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(fileSize);

  if (!file.read(reinterpret_cast<char *>(buffer.data()), fileSize))
  {
    throw std::runtime_error("Failed to read file");
  }

  return buffer;
}

// FIXME: Move it somewhere else
static const uint32_t PALETTE[] = {0xffffffff, 0xaaaaaaff, 0x555555ff, 0x000000ff};

uint32_t convertColor(uint16_t value)
{
  if (value & 0x8000)
  {
    // GB palette
    return PALETTE[value & 0x3];
  }
  // CGB palette
  int red = ((value & 0x1f) * 0xff / 0x1f) | 0;
  int green = (((value >> 5) & 0x1f) * 0xff / 0x1f) | 0;
  int blue = (((value >> 10) & 0x1f) * 0xff / 0x1f) | 0;
  return (red << 24) | (green << 16) | (blue << 8) | 0xff;
}

app::application::application()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
  {
    throw std::runtime_error(SDL_GetError());
  }

  this->mWindow = SDL_CreateWindow("gb-emulator-cpp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (this->mWindow == nullptr)
  {
    throw std::runtime_error(SDL_GetError());
  }

  this->mRenderer = SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (this->mRenderer == nullptr)
  {
    throw std::runtime_error(SDL_GetError());
  }

  // Create frame buffer texture
  this->mPpuTexture = std::make_unique<ppu_texture>(*this);
  this->mFontRenderer = std::make_shared<font_renderer>(*this);

  auto rom = readRom("res/drmario.gb");

  this->mSystem = std::make_shared<gb_system::system>(gb_system::system_type::DMG);
  this->mSystem->mCartridge = std::make_shared<cartridge::cartridge_raw>(rom, *(this->mSystem));
  this->mSystem->reset();
}

void app::application::handle_event(SDL_Event &event)
{
}

void app::application::update()
{
  SDL_RenderClear(this->mRenderer);

  auto &system = *(this->mSystem);

  // Run 1 frame
  int stopClock = system.mCpu->mClocks + 1000;
  while (system.mCpu->mClocks < stopClock)
  {
    system.mInterrupter->step();
    if (!system.mCpu->mIsRunning)
    {
      system.mCpu->mClocks += 1;
      system.tick(1);
    }
  }

  // Update frame buffer
  this->mPpuTexture->update();
  SDL_RenderCopy(this->mRenderer, this->mPpuTexture->mTexture, NULL, NULL);

  this->mFontRenderer->reset();
  this->mFontRenderer->write(std::format("CLK: {}\n", system.mCpu->mClocks));
  this->mFontRenderer->write(std::format("PC: {:04x} ", system.mCpu->mRegister.pc));
  this->mFontRenderer->write(std::format("A: {:02x} ", system.mCpu->mRegister.a));
  this->mFontRenderer->write(std::format("B: {:02x} ", system.mCpu->mRegister.b));
  this->mFontRenderer->write(std::format("C: {:02x} ", system.mCpu->mRegister.c));
  this->mFontRenderer->write(std::format("D: {:02x} ", system.mCpu->mRegister.d));
  this->mFontRenderer->write(std::format("E: {:02x} ", system.mCpu->mRegister.e));
  this->mFontRenderer->write(std::format("F: {:02x} ", system.mCpu->mRegister.f));
  this->mFontRenderer->write(std::format("HL: {:04x}\n", system.mCpu->mRegister.hl()));
  this->mFontRenderer->write(std::format("LY: {:02x}", system.mPpu->mLy));

  SDL_RenderPresent(this->mRenderer);
}

app::application::~application()
{
  this->mSystem = nullptr;
  this->mPpuTexture = nullptr;
  this->mFontRenderer = nullptr;
  if (this->mRenderer != nullptr)
  {
    SDL_DestroyRenderer(this->mRenderer);
    this->mRenderer = nullptr;
  }
  if (this->mWindow != nullptr)
  {
    SDL_DestroyWindow(this->mWindow);
    this->mWindow = nullptr;
  }
}
