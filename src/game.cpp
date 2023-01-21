#include "../include/game.hpp"

#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {
  while (events()) {
    window.clear();

    SDL_SetRenderDrawColor(window.getRenderer(), 200, 200, 200, 255);

    window.flip();
  }
}

bool Game::events() {
  
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return false;
      break;
    
    default:
      break;
    }
  }

  return true;
}