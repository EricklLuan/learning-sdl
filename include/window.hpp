#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <iostream>

class Window {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::unordered_map<std::string, SDL_Texture*> cache;
public:
  Window(const char* title, int width, int height);
  ~Window();

  inline void clear() { SDL_RenderClear(renderer);   }
  inline void flip()  { SDL_RenderPresent(renderer); }

  SDL_Texture* loadTexture(const char* path);

  inline SDL_Window* getWindow()     { return window;   }
  inline SDL_Renderer* getRenderer() { return renderer; }
};
