#include "../include/animated_sprite.hpp"

#include <iostream>

AnimatedSprite::AnimatedSprite(SDL_Texture* texture, Vector2 nSize, int nMaxFrames)
: Sprite(texture, nSize), maxFrames(nMaxFrames){
  
}

void AnimatedSprite::render(SDL_Renderer* renderer, Vector2 position, int vertical, int fps) {
  if (actualFrame >= maxFrames) actualFrame = 0;

  std::cout << actualFrame << "\n";

  SDL_Rect src = {
    (int)size.x * actualFrame,
    (int)size.y * vertical,
    (int)size.x,
    (int)size.y
  };

  SDL_Rect dst = {
    (int)position.x, 
    (int)position.y, 
    (int)size.x, 
    (int)size.y
  };

  actualFrame = (SDL_GetTicks() / (1000 / fps)) % maxFrames;

  SDL_RenderCopy(renderer, sprite_texture, &src, &dst);
}
