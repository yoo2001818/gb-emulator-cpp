#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <memory>
#include "gb_system/system.hpp"

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

class application
{
public:
  void init();
  void loop();
  void destroy();
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  SDL_Texture *mFbTexture;
  SDL_PixelFormat *mFbFmt;
  std::shared_ptr<gb_system::system> system;
};

#endif // __APPLICATION_HPP__
