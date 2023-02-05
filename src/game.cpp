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
  Sprite bg = Sprite(window.loadTexture("assets/bg.png"), Vector2(500, 500));
  Dot dot = Dot(player, Vector2());

  Sprite fps_text = window.loadLabel("", font, Vector4(255, 255, 255));

  SDL_Rect camera = {
    0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
  };

  while (events()) {
    newFrame();
    dot.handleEvent(&input);

    fps_text.setTexture(window.loadLabel("FPS: " + std::to_string(FPS), font, Vector4(255, 255, 255)));
  
    if (input.getKeyPressed(SDL_SCANCODE_ESCAPE) == true) return;
    
    dot.move();

    camera.x = ( dot.getPostion().x + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH/2;
    camera.y = ( dot.getPostion().y + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT/2;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > 1280 - camera.w) camera.x = 1280 - camera.w;
    if (camera.y > 960 - camera.h) camera.y = 960 - camera.h;

    window.clear();
    bg.render(window.getRenderer(), Vector2(camera.x, camera.y), Vector2());
    dot.render(window.getRenderer(), Vector2(camera.x, camera.y));
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

bool Game::checkCollision(SDL_Rect* a, SDL_Rect* b) {
  int leftA = a->x;
  int rightA = a->x + a->w;
  int topA = a->y;
  int bottomA = a->y + a->h;

  int leftB = b->x;
  int rightB = b->x + b->w;
  int topB = b->y;
  int bottomB = b->y + b->h;

  if (bottomA <= topB) return false;
  if (topA >= bottomB) return false;
  if (leftA >= rightB) return false;
  if (rightA <= leftB) return false;

  return true;
}