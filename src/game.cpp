#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include "../include/vector2.hpp"
#include "../include/animated_sprite.hpp"

#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

  AnimatedSprite animated_sprite = AnimatedSprite(window.loadTexture("assets/sprite_sheet.png"), Vector2(64, 205), 3);

  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;

    window.clear();

    animated_sprite.render(window.getRenderer(), Vector2(), 0, 6);

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