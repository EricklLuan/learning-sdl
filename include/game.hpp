#pragma once

#include "./window.hpp"
#include "./input.hpp"

class Game {
private:
  Window window = Window("Learning SDL", 500, 500);
  Input input;
  SDL_Event event;

  bool events();

public:
  
  Game();
  ~Game();

  void run();

};