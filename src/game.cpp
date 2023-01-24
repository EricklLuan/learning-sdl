#include "../include/game.hpp"

#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {
  while (events()) {

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;

    window.clear();

    SDL_Rect viewport = {
      0, 0,
      SCREEN_WIDTH / 2,
      SCREEN_HEIGHT / 2,
    };

    SDL_RenderSetViewport(window.getRenderer(), &viewport);

    SDL_RenderCopy(window.getRenderer(), window.loadTexture("assets/mario.png"), NULL, NULL);

    SDL_Rect top_right_viewport = {
      SCREEN_WIDTH / 2,
      0,
      SCREEN_WIDTH / 2,
      SCREEN_HEIGHT / 2,
    };

    SDL_RenderSetViewport(window.getRenderer(), &top_right_viewport);

    SDL_RenderCopy(window.getRenderer(), window.loadTexture("assets/mario.png"), NULL, NULL);

    SDL_Rect bottom_viewport = {
      0,
      SCREEN_HEIGHT / 2,
      SCREEN_WIDTH,
      SCREEN_HEIGHT / 2,
    };

    SDL_RenderSetViewport(window.getRenderer(), &bottom_viewport);

    SDL_RenderCopy(window.getRenderer(), window.loadTexture("assets/mario.png"), NULL, NULL);

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