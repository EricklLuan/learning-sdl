#pragma once

#include <map>
#include <SDL2/SDL.h>

class Input {
private:
  std::map<SDL_Scancode, bool> _relesead;
  std::map<SDL_Scancode, bool> _pressed;
  std::map<SDL_Scancode, bool> _held;
public:

  void new_frame();

  void key_down_event(SDL_Event &event);
  void key_up_event(SDL_Event &event);

  bool getKeyRelesead(SDL_Scancode key);
  bool getKeyPressed(SDL_Scancode key);
  bool getKeyHeld(SDL_Scancode key);
};