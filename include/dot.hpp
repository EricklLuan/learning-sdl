#pragma once

#include "./input.hpp"
#include "./vector2.hpp"
#include "./sprite.hpp"

class Dot {
private:
  Vector2 position;
  Vector2 velocity;

  Sprite sprite;

  SDL_Rect collider;

public:
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;

  static const int DOT_VEL =  5;

  Dot(Sprite texture, Vector2 _position);

  void handleEvent(Input* input);

  bool checkCollision(SDL_Rect* a, SDL_Rect* b);

  void move(SDL_Rect& wall);
  void render(SDL_Renderer* renderer);
};