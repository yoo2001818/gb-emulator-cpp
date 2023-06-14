#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <memory>
#include "../gb_system/system.hpp"
#include "ppu_texture.hpp"
#include "font_renderer.hpp"

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

namespace app
{
  class application
  {
  public:
    application();
    ~application();
    void handle_event(SDL_Event &event);
    void update();
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    std::unique_ptr<ppu_texture> mPpuTexture;
    std::shared_ptr<font_renderer> mFontRenderer;
    std::shared_ptr<gb_system::system> mSystem;
  };
}

#endif // __APPLICATION_HPP__
