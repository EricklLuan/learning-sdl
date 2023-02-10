#pragma once

#include "../include/sprite.hpp"
#include "../include/input.hpp"

#include <SDL2/SDL_ttf.h>
#include <unordered_map>

class Window {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::unordered_map<std::string, SDL_Texture*> cache;

  Vector2 size;

  bool mouseFocus;
  bool keyboardFocus;
  bool fullScreen;
  bool minimized;
  bool isOpen;

  int id;
public:
  Input input;

  Window(const char* title, int width, int height);
  ~Window();

  void clear();
  void flip();
  void focus();
  void render();

  bool handleEvent(SDL_Event &event);

  SDL_Texture* loadTexture(const char* path);
  TTF_Font* loadFont(const char* path, int size);
  Sprite loadLabel(std::string text, TTF_Font* font, Vector4 color);

  inline bool hasMouseFocus() { return mouseFocus; }
  inline bool hasKeyboardFocus() { return keyboardFocus; }
  inline bool isMinimized() { return minimized; }
  inline bool isWOpen() { return isOpen; }
  inline SDL_Window* getWindow()     { return window;   }
  inline SDL_Renderer* getRenderer() { return renderer; }
};
