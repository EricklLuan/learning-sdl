#include "../include/game.hpp"
#include "../include/sprite.hpp"

#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

  TTF_Font* font = window.loadFont("fonts/FreePixel.ttf", 50);
  Sprite text = window.loadLabel("Hello Word", font, Vector4(255, 255, 255));

  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    if (input.getKeyPressed(SDL_SCANCODE_E) == true) {
      text.setTexture(window.loadLabel("Changed", font, Vector4(255, 255, 255)));
    }

    text.angle += 0.01;

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