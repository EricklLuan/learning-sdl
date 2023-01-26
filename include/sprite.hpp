#pragma once

#include <SDL2/SDL.h>

#include "./vector2.hpp"
#include "./vector4.hpp"

class Sprite {
protected:
  SDL_Texture* sprite_texture;
  Vector2 size;
  SDL_Point* center;
public:
  float angle = 0.0f;
  SDL_RendererFlip flip = SDL_FLIP_NONE;

  Sprite(SDL_Texture* texture, Vector2 nSize);
  ~Sprite();

  void free();

  void modulate(Vector4 color);
  void tranparency(float level);

  virtual void render(SDL_Renderer* renderer, Vector2 position, Vector2 sprite);

  inline Vector2 getSize() { return size; }
  
  void setCenter(SDL_Point* nCenter);  
};