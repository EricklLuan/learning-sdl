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

  Sprite player = Sprite(window.loadTexture("assets/dot.png"), Vector2(20, 20));
  Dot dot = Dot(player, Vector2(
    HORIZONTAL_CENTER - 10,
    VERTICAL_CENTER - 10
  ));

  Sprite fps_text = window.loadLabel("", font, Vector4(255, 255, 255));

  while (events()) {
    newFrame();
    dot.handleEvent(&input);

    fps_text.setTexture(window.loadLabel("FPS: " + std::to_string(FPS), font, Vector4(255, 255, 255)));

    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    
    dot.move();

    window.clear();

    dot.render(window.getRenderer());
    fps_text.render(window.getRenderer(), Vector2(10, 10), Vector2());

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