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
  void update_pixels();
  void handle_event(SDL_Event &event);
  void update();
  void destroy();
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  SDL_Texture *mFbTexture;
  SDL_PixelFormat *mFbFormat;
  std::shared_ptr<gb_system::system> mSystem;
};

#endif // __APPLICATION_HPP__
