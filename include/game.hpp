#pragma once

#include "./window.hpp"
#include "./input.hpp"
#include "./timer.hpp"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const int VERTICAL_CENTER = SCREEN_HEIGHT / 2;
const int HORIZONTAL_CENTER = SCREEN_WIDTH / 2;

const int FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

class Game {
private:
  Window window = Window("Learning SDL", SCREEN_WIDTH, SCREEN_HEIGHT);
  Input input;
  SDL_Event event;

  TTF_Font* font;

  Timer capFps;
  Timer countFps;
  int frames = 0;
  float FPS;

  bool events();

  void newFrame();
  void endFrame();
  bool checkCollision(SDL_Rect* a, SDL_Rect* b);

public:
  
  Game();
  ~Game();

  void run();

};