#include "../include/game.hpp"
#include "../include/label.hpp"

#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

  Label text = Label(window.getRenderer(), "Hello Word :)", {0, 0, 0});

  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;

    window.clear();
    text.render(window.getRenderer(), Vector2((SCREEN_WIDTH - text.getSize().x)/2, (SCREEN_HEIGHT - text.getSize().y)/2));
    SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
    window.flip();
  }
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