#pragma once

#include "./window.hpp"

class Game {
private:
  Window window = Window("Learning SDL", 500, 500);
  SDL_Event event;

  bool events();

public:
  
  Game();
  ~Game();

  void run();

};