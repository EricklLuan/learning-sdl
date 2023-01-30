#pragma once

#include <SDL2/SDL.h>

#include "./vector2.hpp"
#include "./vector4.hpp"

class Sprite {
protected:
  SDL_Texture* sprite_texture;
  Vector2 size;
  
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Point* center = NULL;
  
  bool flipH = false;
  bool flipV = false;


public:
  float angle = 0.0f;

  Sprite(SDL_Texture* texture, Vector2 nSize);
  ~Sprite();

  void free();

  void modulate(Vector4 color);
  void tranparency(float level);

  virtual void render(SDL_Renderer* renderer, Vector2 position, Vector2 sprite);

  inline SDL_Texture* getTexture() { return sprite_texture; }
  inline Vector2 getSize() { return size; }
  inline bool getFlipH() { return flipH; }
  inline bool getFlipV() { return flipV; }
  
  void setCenter(SDL_Point* nCenter);
  void setFlipH(bool isFliped);
  void setFlipV(bool isFliped);

  void setTexture(Sprite nValues);
};