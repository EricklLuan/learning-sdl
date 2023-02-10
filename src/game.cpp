#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include "../include/dot.hpp"

#include <iostream>
#include <sstream>

Game::Game(): font(window[0].loadFont("fonts/FreePixel.ttf", 25)) {
  countFps.start();
}

Game::~Game() {

}

void Game::run() {
    while (!quit) {
    newFrame();

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }

      for (int i=0; i <= 2; i++) {
        if (!window[i].handleEvent(event)) quit = true;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_1:
          window[0].focus();
          break;
        
        case SDLK_2:
          window[1].focus();
          break;

        case SDLK_3:
          window[2].focus();
          break;

        default:
          break;
        }
      }
    }

    for (int i=0; i <= 2; i++) {
      window[i].render();
    }

    bool allClose = true;
    for (int i = 0; i <= 2; i++) {
      if (window[i].isWOpen()) {
        allClose = false;
        break;
      }
    }

    if (allClose) {
      quit = true;
    }
    
    endFrame();
  }
}

void Game::newFrame() {
  capFps.start();

  FPS = frames / ( countFps.getTime() / 1000.f );
  if( FPS > 2000000 ) FPS = 0;
}

void Game::endFrame() {
  ++frames;
  int frameTicks = capFps.getTime();
  if (frameTicks < SCREEN_TICKS_PER_FRAME - frameTicks) {
    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
  }
}
