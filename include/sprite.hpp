#pragma once

#include <SDL2/SDL.h>

#include "./vector2.hpp"
#include "./vector4.hpp"

class Sprite {
private:
  SDL_Texture* sprite_texture;
  Vector2 size;
public:
  Sprite(SDL_Texture* texture, Vector2 nSize);
  ~Sprite();

  void free();
  void modulate(Vector4 color);
  void render(SDL_Renderer* renderer, Vector2 position, Vector2 sprite);

  inline Vector2 getSize() { return size; }

};