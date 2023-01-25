#include "../include/sprite.hpp"

#include <iostream>


Sprite::Sprite(SDL_Texture* texture, Vector2 nSize)
: sprite_texture(texture), size(nSize) {
  
}

Sprite::~Sprite() {
  
}

void Sprite::free() {
  
}

void Sprite::modulate(Vector4 color) {
  SDL_SetTextureColorMod(sprite_texture, color.r, color.g, color.b);
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

  SDL_RenderCopy(renderer, sprite_texture, &src, &dst);
}
