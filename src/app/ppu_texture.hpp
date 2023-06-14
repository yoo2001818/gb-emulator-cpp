#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#ifndef __PPU_TEXTURE_HPP__
#define __PPU_TEXTURE_HPP__

namespace app
{
  class application;
  class ppu_texture
  {
  public:
    ppu_texture(application &pApp);
    ~ppu_texture();
    uint32_t convert_color(uint16_t pValue);
    void update();
    SDL_Texture *mTexture;
    SDL_PixelFormat *mPixelFormat;

  private:
    application &mApp;
  };
}

#endif // __PPU_TEXTURE_HPP__
