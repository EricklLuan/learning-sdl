#pragma once

#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "./vector2.hpp"

class Label {
private:
  SDL_Texture* texture;
  Vector2 size;
  std::string text;

  TTF_Font* font;

  SDL_Point* center = NULL;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  bool flipH = false;
  bool flipV = false;
  float angle = 0.0f;

public:

  Label(SDL_Renderer* renderer, std::string nText, SDL_Color color);

  void render(SDL_Renderer* renderer, Vector2 position);
  
  inline std::string getText() { return text; }
  inline Vector2 getSize() { return size; }

  void setCenter(SDL_Point* nCenter);
  void setFlipH(bool isFliped);
  void setFlipV(bool isFliped);

};