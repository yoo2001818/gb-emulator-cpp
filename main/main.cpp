#include "../src/app/application.hpp"
#include "../src/cartridge/cartridge_raw.hpp"
#include "../src/gb_system/system.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

int main_app() {
  {
    app::application app;

    while (true) {
      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
        app.handle_event(event);
      }

      uint64_t beginTime = SDL_GetTicks64();

      app.update();

      uint64_t endTime = SDL_GetTicks64();
      int32_t deltaTime = static_cast<int32_t>(endTime - beginTime);
      int32_t sleepTime = 12 - deltaTime;

      if (sleepTime > 0) {
        SDL_Delay(sleepTime);
      }
    }
  }
  SDL_Quit();

  return 0;
}
