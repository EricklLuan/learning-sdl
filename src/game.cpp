#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}
// create viewport class
void Game::run() {
  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;

    window.clear();

    Sprite sprite = Sprite(window.loadTexture("assets/sprites.png"), 100, 100);

    sprite.render(window.getRenderer(), 0, 0, 1, 1);
    sprite.render(window.getRenderer(), SCREEN_WIDTH - 100, 0, 2, 1);
    sprite.render(window.getRenderer(), 0, SCREEN_HEIGHT - 100, 1, 2);
    sprite.render(window.getRenderer(), SCREEN_HEIGHT - 100, SCREEN_HEIGHT - 100, 2, 2);

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