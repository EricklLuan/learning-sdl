#include "../include/sprite.hpp"

#include <iostream>


Sprite::Sprite(SDL_Texture* texture, int nWidth, int nHeight): 
sprite(texture), width(nWidth), height(nHeight)  {
  
}

Sprite::~Sprite() {
  
}

void Sprite::free()
{
  
}

void Sprite::render(SDL_Renderer* renderer, int x, int y, int line, int column) {
  SDL_Rect dst = {
    x, 
    y, 
    width, 
    height
  };

  SDL_Rect src = {
    width * line,
    height * column,
    width,
    height
  };

  SDL_RenderCopy(renderer, sprite, &src, &dst);
}

int Sprite::getWidth()
{
  return width;
}

int Sprite::getHeight()
{
  return height;
}
