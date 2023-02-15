#pragma once

#include "./vector2.hpp"
#include "./vector4.hpp"

#include <SDL2/SDL.h>

class Sprite {
protected:
  SDL_Texture* sprite_texture;
  SDL_Surface* pixels;
  Vector2 size;
  
  SDL_RendererFlip flip;
  SDL_Point* center;
  
  bool flipH = false;
  bool flipV = false;


public:
  float angle = 0.0f;

  Sprite(SDL_Texture* texture=NULL, Vector2 nSize=Vector2());
  ~Sprite();

  void free();

  void modulate(Vector4 color);
  void tranparency(float level);

  void loadPixelFromFile(const char* path, SDL_Window* window);
  void loadFromPixels(SDL_Renderer* renderer);

  virtual void render(SDL_Renderer* renderer, Vector2 position, Vector2 sprite);

  inline SDL_Texture* getTexture() { return sprite_texture; }
  inline SDL_Point* getCenter() { return center; }
  inline Vector2 getSize() { return size; }
  inline bool getFlipH() { return flipH; }
  inline bool getFlipV() { return flipV; }
  Uint32* getPixels32();
  Uint32  getPitch32();
  
  void setCenter(SDL_Point* nCenter);
  void setFlipH(bool isFliped);
  void setFlipV(bool isFliped);
  inline void setSize(Vector2 nsize) { size = nsize; }

  void setTexture(Sprite nValues);
};