#pragma once

#include <SDL2/SDL.h>

class Sprite {
private:
  SDL_Texture* sprite;
  int width;
  int height;
public:
  Sprite(SDL_Texture* texture, int nWidth, int nHeight);
  ~Sprite();

  void free();
  void render(SDL_Renderer* renderer, int x=0, int y=0, int line=0, int column=0);

  int getWidth();
  int getHeight();

};