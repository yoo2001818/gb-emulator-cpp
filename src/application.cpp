#include <fstream>
#include <vector>
#include <format>
#include "application.hpp"
#include "cartridge/cartridge_raw.hpp"

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

void application::init()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
  {
    throw std::runtime_error(std::format("Unable to initialize SDL: {}", SDL_GetError()));
  }

  this->mWindow = SDL_CreateWindow("gb-emulator-cpp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
  if (this->mWindow == nullptr)
  {
    throw std::runtime_error(std::format("Unable to create window: {}", SDL_GetError()));
  }

  this->mRenderer = SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (this->mRenderer == nullptr)
  {
    throw std::runtime_error(std::format("Unable to create renderer: {}", SDL_GetError()));
  }

  // Create frame buffer texture
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  this->mFbTexture = SDL_CreateTexture(this->mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, gb_system::LCD_WIDTH, gb_system::LCD_HEIGHT);
  if (this->mFbTexture == nullptr)
  {
    throw std::runtime_error(std::format("Unable to create texture: {}", SDL_GetError()));
  }

  this->mFbFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  if (this->mFbFormat == nullptr)
  {
    throw std::runtime_error(std::format("Unable to create format: {}", SDL_GetError()));
  }

  auto rom = readRom("res/drmario.gb");

  this->mSystem = std::make_shared<gb_system::system>(gb_system::system_type::DMG);
  this->mSystem->mCartridge = std::make_shared<cartridge::cartridge_raw>(rom, *(this->mSystem));
  this->mSystem->reset();
}

void application::update_pixels()
{
  uint32_t *pixels;
  int pitch;
  int result;
  result = SDL_LockTexture(this->mFbTexture, NULL, reinterpret_cast<void **>(&pixels), &pitch);
  if (result != 0)
  {
    SDL_Log("Unable to lock texture: %s", SDL_GetError());
    return;
  }

  auto &framebuffer = this->mSystem->mPpu->mFramebuffer;
  for (int y = 0; y < gb_system::LCD_HEIGHT; y += 1)
  {
    for (int x = 0; x < gb_system::LCD_WIDTH; x += 1)
    {
      uint16_t pixel = framebuffer[y * gb_system::LCD_WIDTH + x];
      uint32_t color = convertColor(pixel);
      pixels[y * gb_system::LCD_WIDTH + x] = SDL_MapRGBA(this->mFbFormat, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
    }
  }

  SDL_UnlockTexture(this->mFbTexture);
}

void application::handle_event(SDL_Event &event)
{
}

void application::update()
{
  SDL_RenderClear(this->mRenderer);

  auto &system = *(this->mSystem);

  // Run 1 frame
  int stopClock = system.mCpu->mClocks + 17556;
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
  this->update_pixels();
  SDL_RenderCopy(this->mRenderer, this->mFbTexture, NULL, NULL);

  SDL_RenderPresent(this->mRenderer);
}

void application::destroy()
{
  this->mSystem = nullptr;

  if (this->mFbTexture != nullptr)
  {
    SDL_DestroyTexture(this->mFbTexture);
    this->mFbTexture = nullptr;
  }
  if (this->mFbFormat != nullptr)
  {
    SDL_FreeFormat(this->mFbFormat);
    this->mFbFormat = nullptr;
  }
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
