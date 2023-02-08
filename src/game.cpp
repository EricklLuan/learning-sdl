#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include "../include/dot.hpp"

#include <iostream>
#include <sstream>

Game::Game(): font(window.loadFont("fonts/FreePixel.ttf", 25)) {
  countFps.start();
}

Game::~Game() {

}

void Game::run() {

  
  while (window.handleEvent(event)) {
    newFrame();

    if (window.input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    
    window.clear();
    window.flip();
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
