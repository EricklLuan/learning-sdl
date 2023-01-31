#pragma once

#include "../include/sprite.hpp"

#include <SDL2/SDL_ttf.h>
#include <unordered_map>

class Window {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::unordered_map<std::string, SDL_Texture*> cache;
public:
  Window(const char* title, int width, int height);
  ~Window();

  void clear();
  void flip(); 

  SDL_Texture* loadTexture(const char* path);
  TTF_Font* loadFont(const char* path, int size);
  Sprite loadLabel(std::string text, TTF_Font* font, Vector4 color);

  inline SDL_Window* getWindow()     { return window;   }
  inline SDL_Renderer* getRenderer() { return renderer; }
};
