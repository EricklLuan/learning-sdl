#pragma once

#include "./input.hpp"
#include "./vector2.hpp"
#include "./sprite.hpp"

#include <vector>

class Dot {
private:
  Vector2 position;
  Vector2 velocity;

  Sprite sprite;

  SDL_Rect collider;
  std::vector<SDL_Rect> colliders;

  void shiftColliders();

public:
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;

  static const int DOT_VEL = 1;

  Dot(Sprite texture, Vector2 _position);

  void handleEvent(Input* input);

  bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

  void move(std::vector<SDL_Rect>& oColliders);
  void render(SDL_Renderer* renderer);

  inline std::vector<SDL_Rect>& getColliders() {return colliders;}
};