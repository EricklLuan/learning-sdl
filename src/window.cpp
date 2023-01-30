#include "../include/window.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

Window::Window(const char* title, int width, int height) {
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL::INIT::ERROR: " << SDL_GetError() << "\n";
  }

  if (!IMG_Init(IMG_INIT_JPG)) {
    std::cout << "IMG::INIT::ERROR: " << IMG_GetError() << "\n";
  }

  if (TTF_Init() != 0) {
    std::cout << "TTF::INIT::ERROR: " << TTF_GetError() << "\n";
  }

  window = SDL_CreateWindow(
    title, 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    width, 
    height, 
    SDL_WINDOW_OPENGL
  );

  if (window == NULL) {
    std::cout << "SDL::WINDOW::CREATE::ERROR: " << SDL_GetError() << "\n";
  };

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
  );

  if (renderer == NULL) {
    std::cout << "SDL::RENDERER::CREATE::ERROR: " << SDL_GetError() << "\n";
  }
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

SDL_Texture* Window::loadTexture(const char* path) {

  if (cache.find(path) != cache.end()) {
    return cache[path];
  } else {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path);

    if (surface == NULL) std::cout << "IMG::LOAD::SURFACE::ERROR: " << IMG_GetError() << "\n";
    else {
      texture = SDL_CreateTextureFromSurface(renderer, surface);
      if (texture == NULL) std::cout << "SDL::LOAD::TEXTURE::ERROR: " << SDL_GetError() << "\n";

      SDL_FreeSurface(surface); 
    }

    if (texture != NULL) {
      cache[path] = texture;
    }

    return texture;
  }
}

TTF_Font* Window::loadFont(const char* path, int size) {
  TTF_Font* font = TTF_OpenFont(path, size);
  if (font == NULL) {
    std::cout << "TTF::LOAD::ERROR: " << TTF_GetError() << "\n";
    return NULL;
  }

  return font;
}

Sprite Window::loadLabel(const char* text, TTF_Font* font, Vector4 color) {
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b});

  if (surface == NULL) {
    std::cout << "SDL::SURFACE::CREATE::ERROR: " << SDL_GetError() << "\n";
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == NULL) {
    std::cout << "SDL::TEXTURE::CREATE::ERROR: " << SDL_GetError() << "\n";
  }

  Vector2 size;
  size.x = surface->w;
  size.y = surface->h;

  SDL_FreeSurface(surface);

  return {texture, size};
}