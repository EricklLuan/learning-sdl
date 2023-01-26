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
  Sprite mario = Sprite(window.loadTexture("assets/mario.png"), Vector2(91, 184));
  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;

    window.clear();

    if (input.getKeyHeld(SDL_SCANCODE_F)) {mario.angle += 0.5f;}
    if (input.getKeyHeld(SDL_SCANCODE_J)) {mario.angle -= 0.5f;}

    if (input.getKeyPressed(SDL_SCANCODE_H)) { mario.setFlipH(!mario.getFlipH()); }

    mario.render(window.getRenderer(), Vector2((SCREEN_WIDTH/2) - (91/2), (SCREEN_HEIGHT/2) - (184/2)), Vector2(0, 0));

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