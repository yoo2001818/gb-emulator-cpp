#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "gb_system/system.hpp"

int main()
{

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window;

  window = SDL_CreateWindow("CppGameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);

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

  auto system = gb_system::system(gb_system::system_type::CGB);
  system.mCpu->step();

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

    //

    uint64_t endTime = SDL_GetTicks64();
    int32_t deltaTime = static_cast<int32_t>(endTime - beginTime);
    int32_t sleepTime = 12 - deltaTime;

    if (sleepTime > 0)
    {
      SDL_Delay(sleepTime);
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
