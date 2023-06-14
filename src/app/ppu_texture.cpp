#include "ppu_texture.hpp"
#include "application.hpp"

app::ppu_texture::ppu_texture(application &pApp) : mApp(pApp)
{
  // Create frame buffer texture
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  this->mTexture = SDL_CreateTexture(this->mApp.mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, gb_system::LCD_WIDTH, gb_system::LCD_HEIGHT);
  if (this->mTexture == nullptr)
  {
    throw std::runtime_error(SDL_GetError());
  }

  this->mPixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  if (this->mPixelFormat == nullptr)
  {
    throw std::runtime_error(SDL_GetError());
  }
}

app::ppu_texture::~ppu_texture()
{
  if (this->mTexture != nullptr)
  {
    SDL_DestroyTexture(this->mTexture);
    this->mTexture = nullptr;
  }
  if (this->mPixelFormat != nullptr)
  {
    SDL_FreeFormat(this->mPixelFormat);
    this->mPixelFormat = nullptr;
  }
}

static const uint32_t MONOCHROME_PALETTE[] = {0xffffffff, 0xaaaaaaff, 0x555555ff, 0x000000ff};

uint32_t app::ppu_texture::convert_color(uint16_t pValue)
{
  if (pValue & 0x8000)
  {
    // GB palette
    return MONOCHROME_PALETTE[pValue & 0x3];
  }
  // CGB palette
  int red = ((pValue & 0x1f) * 0xff / 0x1f) | 0;
  int green = (((pValue >> 5) & 0x1f) * 0xff / 0x1f) | 0;
  int blue = (((pValue >> 10) & 0x1f) * 0xff / 0x1f) | 0;
  return (red << 24) | (green << 16) | (blue << 8) | 0xff;
}

void app::ppu_texture::update()
{
  uint32_t *pixels;
  int pitch;
  int result;
  result = SDL_LockTexture(this->mTexture, NULL, reinterpret_cast<void **>(&pixels), &pitch);
  if (result != 0)
  {
    SDL_Log("Unable to lock texture: %s", SDL_GetError());
    return;
  }

  auto &framebuffer = this->mApp.mSystem->mPpu->mFramebuffer;
  for (int y = 0; y < gb_system::LCD_HEIGHT; y += 1)
  {
    for (int x = 0; x < gb_system::LCD_WIDTH; x += 1)
    {
      uint16_t pixel = framebuffer[y * gb_system::LCD_WIDTH + x];
      uint32_t color = this->convert_color(pixel);
      pixels[y * gb_system::LCD_WIDTH + x] = SDL_MapRGBA(this->mPixelFormat, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
    }
  }

  SDL_UnlockTexture(this->mTexture);
}
