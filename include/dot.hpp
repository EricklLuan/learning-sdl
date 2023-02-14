#pragma once

#include "./input.hpp"
#include "./vector2.hpp"
#include "./sprite.hpp"
#include "./particle.hpp"

#include <vector>

class Dot {
private:
  Vector2 position;
  Vector2 velocity;

  Sprite sprite;

public:
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;

  static const int DOT_VEL = 5;

  Dot(Sprite texture, Vector2 _position);

  ~Dot();

  void handleEvent(Input* input);

  void move();
  void render(SDL_Renderer* renderer, Vector2 camera_positon);

  inline Vector2 getPostion() { return position; }

};