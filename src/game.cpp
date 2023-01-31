#include "../include/game.hpp"
#include "../include/sprite.hpp"

#include <iostream>
#include <sstream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

  TTF_Font* font = window.loadFont("fonts/FreePixel.ttf", 25);
  Sprite text = window.loadLabel("", font, Vector4(255, 255, 255));

  int startTime = 0;
  std::stringstream message;

  while (events()) {

    message.str("");
    message << "Milliseconds since start time " << SDL_GetTicks() - startTime;

    text.setTexture(window.loadLabel(message.str(), font, Vector4(255, 255, 255)));
    
    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    if (input.getKeyPressed(SDL_SCANCODE_E) == true) {
      startTime = SDL_GetTicks();
    }

    window.clear();

    text.render(
      window.getRenderer(), 
      Vector2((SCREEN_WIDTH/2) - (text.getSize().x/2), (SCREEN_HEIGHT/2) - (text.getSize().y/2)), 
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