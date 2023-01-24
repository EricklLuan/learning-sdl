#include "../include/window.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

Window::Window(const char* title, int width, int height) {
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL::INIT::ERROR: " << SDL_GetError() << "\n";
  }

  if (!IMG_Init(IMG_INIT_JPG)) {
    std::cout << "IMG::INIT::ERROR: " << IMG_GetError() << "\n";
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
