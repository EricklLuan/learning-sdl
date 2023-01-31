#pragma once

#include "./window.hpp"
#include "./input.hpp"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

const int VERTICAL_CENTER = SCREEN_HEIGHT / 2;
const int HORIZONTAL_CENTER = SCREEN_WIDTH / 2;

class Game {
private:
  Window window = Window("Learning SDL", SCREEN_WIDTH, SCREEN_HEIGHT);
  Input input;
  SDL_Event event;

  bool events();

public:
  
  Game();
  ~Game();

  void run();

};