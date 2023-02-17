#include "../include/window.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>

Window::Window(const char* title, int width, int height)
:size(Vector2(width, height)), mouseFocus(true), keyboardFocus(true), fullScreen(false), minimized(false), isOpen(true) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
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
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );

  if (window == NULL) {
    std::cout << "SDL::WINDOW::CREATE::ERROR: " << SDL_GetError() << "\n";
  };

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (renderer == NULL) {
    std::cout << "SDL::RENDERER::CREATE::ERROR: " << SDL_GetError() << "\n";
  }

  id = SDL_GetWindowID(window);
}

Window::~Window() {
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Window::clear() {
  SDL_RenderClear(renderer);
}

void Window::flip() {
  SDL_RenderPresent(renderer);
}

void Window::focus() {
  if (!isOpen) {
    SDL_ShowWindow(window);
  }

  SDL_RaiseWindow(window);
}

void Window::render() {
  if (!minimized) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    clear();

    flip();
  }
}

bool Window::handleEvent(SDL_Event &event) {
  input.new_frame();

  if (event.type == SDL_KEYDOWN) {
    if (event.key.repeat == 0) input.key_down_event(event);
  }

  if (event.type == SDL_KEYUP) {
    if (event.key.repeat == 0) input.key_up_event(event);
  }

  if (event.type == SDL_WINDOWEVENT && event.window.windowID == id) {
    bool updateCaption = false;
    switch (event.window.event) {

    case SDL_WINDOWEVENT_SHOWN:
      isOpen = true;
      break;
    
    case SDL_WINDOWEVENT_HIDDEN:
      isOpen = false;
      break;

    case SDL_WINDOWEVENT_SIZE_CHANGED:
      size.x = event.window.data1;
      size.y = event.window.data2;
      flip();
      break;

    case SDL_WINDOWEVENT_EXPOSED:
      flip();
      break;
    
    case SDL_WINDOWEVENT_ENTER:
      mouseFocus = true;
      updateCaption = true;
      break;
    
    case SDL_WINDOWEVENT_LEAVE:
      mouseFocus = false;
      updateCaption = true;
      break;
    
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      keyboardFocus = true;
      updateCaption = true;
      break;
    
    case SDL_WINDOWEVENT_FOCUS_LOST:
      keyboardFocus = false;
      updateCaption = true;
      break;
    
    case SDL_WINDOWEVENT_MAXIMIZED:
      minimized = false;
      break;
    
    case SDL_WINDOWEVENT_MINIMIZED:
      minimized = true;
      break;
    
    case SDL_WINDOWEVENT_RESTORED:
      minimized = false;
      break;

    case SDL_WINDOWEVENT_CLOSE:
      SDL_HideWindow(window);

    default:
      if (updateCaption) {
        std::stringstream caption;
        caption << "SDL Tutorial - MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
        SDL_SetWindowTitle(window, caption.str().c_str());
      }

      if (input.getKeyPressed(SDL_SCANCODE_F11) == true) {
        if (fullScreen) {
          SDL_SetWindowFullscreen(window, SDL_FALSE);
          fullScreen = false;
        } else {
          SDL_SetWindowFullscreen(window, SDL_TRUE);
          fullScreen = true;
        }
      }
      break;
    }
  }
  return true;
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

Sprite Window::loadLabel(std::string text, TTF_Font* font, Vector4 color) {
  
  if (text == "") {
    text = "Insert Text Here";
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b});

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