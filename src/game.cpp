#include "../include/game.hpp"
#include "../include/sprite.hpp"

#include <iostream>
#include <sstream>

Game::Game(): font(window.loadFont("fonts/FreePixel.ttf", 25)) {
  countFps.start();
}

Game::~Game() {

}

void Game::run() {

  Sprite text = window.loadLabel("", font, Vector4(255, 255, 255));

  std::stringstream message;

  while (events()) {
    newFrame();

    message.str("");
    message << "FPS " << FPS;

    text.setTexture(window.loadLabel(message.str(), font, Vector4(255, 255, 255)));

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    
    window.clear();

    text.render(
      window.getRenderer(), 
      Vector2(HORIZONTAL_CENTER - text.getSize().x/2, VERTICAL_CENTER - text.getSize().y/2), 
      Vector2()
    );

    window.flip();
    endFrame();
  }

  text.free();
}

bool Game::events() {
  input.new_frame();

  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return false;
      break;
    
    case SDL_KEYDOWN:
      if (event.key.repeat == 0) input.key_down_event(event);
      break;
    
    case SDL_KEYUP:
      input.key_up_event(event);
      break;

    default:
      break;
    }
  }

  return true;
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