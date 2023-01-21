#define SDL_MAIN_HANDLED
#include "../include/game.hpp"

int main() {

  Game* game = new Game();
  game->run();

  return 0;
}