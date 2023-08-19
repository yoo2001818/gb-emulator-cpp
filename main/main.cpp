#include "../src/app/application.hpp"
#include "../src/cartridge/cartridge_raw.hpp"
#include "../src/gb_system/system.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <rom>" << std::endl;
    return 1;
  }
  {
    app::application app(argv[1]);

    static const uint64_t US_PER_FRAME = 1000000 / 60;
    uint64_t prevTime = SDL_GetTicks64() * 1000;

    while (true) {
      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
        app.handle_event(event);
      }

      uint64_t beginTime = SDL_GetTicks64() * 1000;
      while (beginTime > prevTime + US_PER_FRAME) {
        app.update();
        prevTime += US_PER_FRAME;
      }

      SDL_Delay(US_PER_FRAME / 1000);
    }
  }
  SDL_Quit();

  return 0;
}
