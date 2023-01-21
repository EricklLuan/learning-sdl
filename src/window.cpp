#include "../include/window.hpp"

#include <iostream>

Window::Window(const char* title, int width, int height) {
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL::INIT::ERROR: " << SDL_GetError() << "\n";
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
