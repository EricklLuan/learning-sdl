#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include "../include/timer.hpp"

#include <iostream>
#include <sstream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

  TTF_Font* font = window.loadFont("fonts/FreePixel.ttf", 25);
  Sprite text = window.loadLabel("", font, Vector4(255, 255, 255));

  std::stringstream message;

  Timer timer;

  while (events()) {

    message.str("");
    message << "Seconds since start time " << (timer.getTime() / 1000.f);

    text.setTexture(window.loadLabel(message.str(), font, Vector4(255, 255, 255)));
    
    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    
    if (input.getKeyPressed(SDL_SCANCODE_E) == true) {
      if (timer.isStarted()) timer.stop();
      else timer.start();
    }

    if (input.getKeyPressed(SDL_SCANCODE_P) == true) {
      if (timer.isPaused()) timer.play();
      else timer.pause();
    }
    
    window.clear();

    text.render(
      window.getRenderer(), 
      Vector2(HORIZONTAL_CENTER - text.getSize().x/2, VERTICAL_CENTER - text.getSize().y/2), 
      Vector2()
    );

    window.flip();
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