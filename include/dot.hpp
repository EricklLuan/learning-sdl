#pragma once

#include "./input.hpp"
#include "./vector2.hpp"
#include "./sprite.hpp"

class Dot {
private:
  Vector2 position;
  Vector2 velocity;

  Sprite sprite;

public:
  static const int DOT_WIDTH = 100;
  static const int DOT_HEIGHT = 100;

  static const int DOT_VEL =  10;

  Dot(Sprite texture, Vector2 _position);

  void handleEvent(Input* input);

  void move();
  void render(SDL_Renderer* renderer);
};