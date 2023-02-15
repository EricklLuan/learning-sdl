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

  Sprite dot = Sprite();

  SDL_Rect camera = { 0, 0, 500, 500 };

  Sprite mario = Sprite(window.loadTexture("assets/mario.png"), Vector2(500, 500));
  dot.loadPixelFromFile("assets/dot.png", window.getWindow());

  Uint32* pixels = dot.getPixels32();
  int PixelCount = dot.getPitch32() * dot.getSize().y;

  Uint32 colorKey = SDL_MapRGBA(SDL_GetWindowSurface(window.getWindow())->format, 0xff, 0xff, 0xff, 0xff);
  Uint32 tranparent = SDL_MapRGBA(SDL_GetWindowSurface(window.getWindow())->format, 0xff, 0xff, 0x00, 0xff);

  for (int i = 0; i < PixelCount; i++) {
    if (pixels[i] == colorKey) {
      pixels[i] = tranparent;
    }
  }
  
  dot.loadFromPixels(window.getRenderer());
  Dot player = Dot(dot, Vector2(20, 20));

  while (!quit) {
    newFrame();

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }

      window.handleEvent(event);
      player.handleEvent(&window.input);
    }

    player.move();

    camera.x = ( player.getPostion().x + Dot::DOT_WIDTH/2 ) - SCREEN_WIDTH/2;
    camera.y = ( player.getPostion().y + Dot::DOT_HEIGHT/2 ) - SCREEN_HEIGHT/2;
    
    if (camera.x < 0) camera.x=0;
    if (camera.y < 0) camera.y=0;
    if (camera.x > 1280 - camera.w) camera.x = 1280 - camera.w;
    if (camera.y > 960 - camera.h) camera.y = 960 - camera.h;

    window.clear();
    mario.render(window.getRenderer(), Vector2((-camera.x) + (1280/2 - 500/2), (-camera.y) + (960/2 - 500/2)), Vector2());
    player.render(window.getRenderer(), Vector2(camera.x, camera.y));
    window.flip();

    endFrame();
  }
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
