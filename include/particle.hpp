#pragma once

#include "./vector2.hpp"
#include "./sprite.hpp"

#include <SDL2/SDL.h>

class Particle {
private:
  Vector2 position;
  int frame;

  Sprite texture;
public:

  Particle(Sprite texture, Vector2 start_positon);

  void render(SDL_Renderer* renderer);
  bool isDead();

};