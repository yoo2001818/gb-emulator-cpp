#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "gb_system/system.hpp"
#include "cartridge/cartridge_raw.hpp"

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

int main()
{

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window;

  window = SDL_CreateWindow("CppGameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

  if (window == nullptr)
  {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr)
  {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    return 1;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, gb_system::LCD_WIDTH, gb_system::LCD_HEIGHT);
  if (texture == nullptr)
  {
    SDL_Log("Unable to create texture: %s", SDL_GetError());
    return 1;
  }

  SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  if (fmt == nullptr)
  {
    SDL_Log("Unable to create pixel format: %s", SDL_GetError());
    return 1;
  }

  auto rom = readRom("res/drmario.gb");

  auto system = gb_system::system(gb_system::system_type::CGB);
  system.mCartridge = std::make_shared<cartridge::cartridge_raw>(rom, system);
  system.reset();

  while (true)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        break;
      }
      //
    }

    uint64_t beginTime = SDL_GetTicks64();

    SDL_RenderClear(renderer);

    // Run 1 frame
    for (int i = 0; i < 17556; i += 1)
    {
      system.tick(1);
    }

    // Draw PPU's framebuffer onto the screen
    uint32_t *pixels;
    int pitch;
    int result;
    result = SDL_LockTexture(texture, NULL, reinterpret_cast<void **>(&pixels), &pitch);
    if (result != 0)
    {
      SDL_Log("Unable to lock texture: %s", SDL_GetError());
      return 1;
    }

    for (int y = 0; y < gb_system::LCD_HEIGHT; y += 1)
    {
      for (int x = 0; x < gb_system::LCD_WIDTH; x += 1)
      {
        uint16_t pixel = system.mPpu->mFramebuffer[y * gb_system::LCD_WIDTH + x];
        uint32_t color = convertColor(pixel);
        pixels[y * gb_system::LCD_WIDTH + x] = SDL_MapRGBA(fmt, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
      }
    }

    SDL_UnlockTexture(texture);
    result = SDL_RenderCopy(renderer, texture, NULL, NULL);
    if (result != 0)
    {
      SDL_Log("Unable to copy texture: %s", SDL_GetError());
      return 1;
    }

    SDL_RenderPresent(renderer);

    uint64_t endTime = SDL_GetTicks64();
    int32_t deltaTime = static_cast<int32_t>(endTime - beginTime);
    int32_t sleepTime = 12 - deltaTime;

    if (sleepTime > 0)
    {
      SDL_Delay(sleepTime);
    }
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
