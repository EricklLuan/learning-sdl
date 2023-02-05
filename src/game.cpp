#include "../include/game.hpp"
#include "../include/sprite.hpp"
#include "../include/dot.hpp"

#include <iostream>
#include <sstream>

Game::Game(): font(window.loadFont("fonts/FreePixel.ttf", 25)) {
  countFps.start();
}

Game::~Game() {

}

void Game::run() {

  Sprite inputTextTexture = window.loadLabel("", font, Vector4(0xFF, 0xFF, 0xFF, 0xFF));

  SDL_StartTextInput();

  while (events()) {
    newFrame();

    inputTextTexture.setTexture(window.loadLabel(inputText, font, Vector4(255, 255, 255, 255)));

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    
    window.clear();

    inputTextTexture.render(window.getRenderer(), Vector2(
      HORIZONTAL_CENTER - (inputTextTexture.getSize().x/2),
      VERTICAL_CENTER - (inputTextTexture.getSize().y/2)
    ), Vector2());

    window.flip();
    endFrame();
  }
}

bool Game::events() {
  input.new_frame();

  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return false;
      break;
    
    case SDL_KEYDOWN:
      if (event.key.repeat == 0) input.key_down_event(event);
      if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
        inputText.pop_back();
      } else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
        SDL_SetClipboardText(inputText.c_str());
      } else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
        inputText += SDL_GetClipboardText();
      }
      break;
    case SDL_TEXTINPUT:
      if (event.type == SDL_TEXTINPUT) {
        if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V'))) {
          inputText += event.text.text;
        }
      }
    break;
    case SDL_KEYUP:
      input.key_up_event(event);
      break;

    default:
      break;
    }
  }

  return true;
}

void Game::newFrame() {
  capFps.start();

  FPS = frames / ( countFps.getTime() / 1000.f );
  if( FPS > 2000000 ) FPS = 0;
}

void Game::endFrame() {
  ++frames;
  int frameTicks = capFps.getTime();
  if (frameTicks < SCREEN_TICKS_PER_FRAME - frameTicks) {
    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
  }
}
