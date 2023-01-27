#include "../include/label.hpp"

#include <iostream>

Label::Label(SDL_Renderer* renderer, std::string nText, SDL_Color color): text(nText) {
  
  font = TTF_OpenFont("fonts/FreePixel.ttf", 50);
  if (font == NULL) std::cout << "TTF::FONT::ERROR: " << TTF_GetError() << "\n";
  else {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (surface != NULL) {
      texture = SDL_CreateTextureFromSurface(renderer, surface);
      if (texture != NULL) {
        size.x = surface->w;
        size.y = surface->h;
      } else  {
        std::cout << "SDL::TEXTURE::CREATE::ERROR: " << SDL_GetError() << "\n";
      }

      SDL_FreeSurface(surface);
    } else {
      std::cout << "SDL::SURFACE::CREATE::ERROR: " << SDL_GetError() << "\n";
    }
  }
}

void Label::render(SDL_Renderer* renderer, Vector2 position) {
  SDL_Rect src = {
    0,
    0,
    (int)size.x,
    (int)size.y
  };

  SDL_Rect dst = {
    (int)position.x, 
    (int)position.y, 
    (int)size.x, 
    (int)size.y
  };

  SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, center, flip);
}

void Label::setCenter(SDL_Point* nCenter) {
  center = nCenter;
}

void Label::setFlipH(bool isFliped) {
  flipH = isFliped;
  if (flipH == true) flip = SDL_FLIP_HORIZONTAL;
  else flip = SDL_FLIP_NONE;
}

void Label::setFlipV(bool isFliped) {
  flipV = isFliped;
  if (flipV == true) flip = SDL_FLIP_VERTICAL;
  else flip = SDL_FLIP_NONE;
}

