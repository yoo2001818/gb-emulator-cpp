#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#ifndef __FONT_RENDERER_HPP__
#define __FONT_RENDERER_HPP__

namespace app
{
  class application;
  class font_renderer
  {
  public:
    font_renderer(application &pApp);
    ~font_renderer();
    void reset();
    void reset(int pPosX, int pPosY);
    void write(char pChar);
    void write(const std::string &pStr);

  private:
    application &mApp;
    SDL_Texture *mTexture;
    int mStartX;
    int mCurrentX;
    int mCurrentY;
  };
}

#endif // __FONT_RENDERER_HPP__
