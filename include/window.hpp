#pragma once

#include <SDL2/SDL.h>

class Window {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
public:
  Window(const char* title, int width, int height);
  ~Window();

  inline void clear() { SDL_RenderClear(renderer);   }
  inline void flip()  { SDL_RenderPresent(renderer); }

  inline SDL_Window* getWindow()     { return window;   }
  inline SDL_Renderer* getRenderer() { return renderer; }
};
