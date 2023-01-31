#include "../include/sprite.hpp"

#include <iostream>


Sprite::Sprite(SDL_Texture* texture, Vector2 nSize)
: sprite_texture(texture), size(nSize) {
  SDL_SetTextureBlendMode(sprite_texture, SDL_BLENDMODE_BLEND);
}

Sprite::~Sprite() {
}

void Sprite::free() {
  SDL_DestroyTexture(sprite_texture);
}

void Sprite::modulate(Vector4 color) {
  SDL_SetTextureColorMod(sprite_texture, color.r, color.g, color.b);
}

void Sprite::tranparency(float level) {
  if (level <= 255 && level >= 0) {
    SDL_SetTextureAlphaMod(sprite_texture, level);
  };
}

void Sprite::render(SDL_Renderer* renderer, Vector2 position, Vector2 sprite) {
  
  SDL_Rect src = {
    (int)size.x * (int)sprite.x,
    (int)size.y * (int)sprite.y,
    (int)size.x,
    (int)size.y
  };

  SDL_Rect dst = {
    (int)position.x, 
    (int)position.y, 
    (int)size.x, 
    (int)size.y
  };

  SDL_RenderCopyEx(renderer, sprite_texture, &src, &dst, angle, center, flip);
}

void Sprite::setCenter(SDL_Point* nCenter) {
  center = nCenter;
}

void Sprite::setFlipH(bool isFliped) {
  flipH = isFliped;
  if (flipH == true) flip = SDL_FLIP_HORIZONTAL;
  else flip = SDL_FLIP_NONE;
}

void Sprite::setFlipV(bool isFliped) {
  flipV = isFliped;
  if (flipV == true) flip = SDL_FLIP_VERTICAL;
  else flip = SDL_FLIP_NONE;
}

void Sprite::setTexture(Sprite nValues) {
  SDL_DestroyTexture(sprite_texture);
  sprite_texture = nValues.getTexture();
  size = nValues.getSize();
}