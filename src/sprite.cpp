#include "../include/sprite.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(SDL_Texture* texture, Vector2 nSize)
: sprite_texture(texture), size(nSize), center(NULL) {
  flip = SDL_FLIP_NONE;
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

void Sprite::loadPixelFromFile(const char* path, SDL_Window* window) {
  free();

  SDL_Surface* surface = IMG_Load(path);

  if (surface == NULL) std::cout << "IMG::LOAD::ERROR: " << IMG_GetError() << "\n";
  else {
    pixels = SDL_ConvertSurfaceFormat(surface, SDL_GetWindowPixelFormat(window), 0);

    if (pixels == NULL) std::cout << "SDL::CONVERT_TO_SURFACE::ERROR: " << SDL_GetError() << "\n";
    else {
      size.x = pixels->w;
      size.y = pixels->h;
    }

    SDL_FreeSurface(surface);
  }
}

void Sprite::loadFromPixels(SDL_Renderer* renderer) {
  if (pixels == NULL) std::cout << "No Pixels Loaded!!";
  else {
    SDL_SetColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, 0, 0xff, 0xff));

    sprite_texture = SDL_CreateTextureFromSurface(renderer, pixels);
    if (sprite_texture == NULL ) std::cout << "SDL::CREATE::TEXTURE::ERROR: " << SDL_GetError() << "\n";
    else {
      size.x = pixels->w;
      size.y = pixels->h;
    }

    SDL_FreeSurface(pixels);
    pixels = NULL;
  }
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

Uint32* Sprite::getPixels32() {
  Uint32* tempo_pixels = NULL;
  if (pixels != NULL) {
    tempo_pixels = static_cast<Uint32*>(pixels->pixels);
  }

  return tempo_pixels;
}


Uint32 Sprite::getPitch32() {
  Uint32 pitch = 0;
  if (pixels != NULL) {
    pitch = pixels->pitch / 4;
  }  

  return pitch;
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