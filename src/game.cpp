#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include "../include/vector2.hpp"

#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {
  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;

    window.clear();

    Sprite sprite = Sprite(window.loadTexture("assets/sprites.png"), Vector2(100, 100));

    sprite.render(window.getRenderer(), Vector2(), Vector2(1, 0));
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