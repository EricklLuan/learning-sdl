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


  SDL_Rect camera = { 0, 0, 500, 500 };

  Sprite mario = Sprite(window.loadTexture("assets/mario.png"), Vector2(500, 500));
  Sprite dot = Sprite(window.loadTexture("assets/dot.png"), Vector2(20, 20));

  Dot player = Dot(dot, Vector2(20, 20));

  Sprite text = window.loadLabel("Espere 3 segundos e olhe o console", font, Vector4(255, 255, 255));

  SDL_TimerCallback callback = [](uint32_t timer, void* param){
    std::cout << "Callback called with message: " << reinterpret_cast<char*>(param) << "\n";
    return (Uint32)0;
  };

  SDL_TimerID timerID = SDL_AddTimer(3*1000, callback, const_cast<char*>(reinterpret_cast<const char*>("3 seconds waited!")));

  while (!quit) {
    newFrame();

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }

      window.handleEvent(event);
      player.handleEvent(&window.input);
    }

    float delta = timerStep.getTime() / 1000.f;

    player.move(delta);

    timerStep.start();

    camera.x = ( player.getPostion().x + Dot::DOT_WIDTH/2 ) - SCREEN_WIDTH/2;
    camera.y = ( player.getPostion().y + Dot::DOT_HEIGHT/2 ) - SCREEN_HEIGHT/2;
    
    if (camera.x < 0) camera.x=0;
    if (camera.y < 0) camera.y=0;
    if (camera.x > 1280 - camera.w) camera.x = 1280 - camera.w;
    if (camera.y > 960 - camera.h) camera.y = 960 - camera.h;

    window.clear();
    mario.render(window.getRenderer(), Vector2((-camera.x) + (1280/2 - 500/2), (-camera.y) + (960/2 - 500/2)), Vector2());
    player.render(window.getRenderer(), Vector2(camera.x, camera.y));
    text.render(window.getRenderer(), Vector2((-camera.x) + (1280/2 - text.getSize().x/2), (-camera.y) + (960/2 - text.getSize().y/2)), Vector2());
    window.flip();

    endFrame();
  }

  SDL_RemoveTimer(timerID);
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

