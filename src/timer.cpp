#include "../include/timer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

Timer::Timer() {
  startTime = 0;
  pausedTime = 0;
  paused = false;
  started = false;
}

void Timer::start() {
  started = true;
  paused = false;

  startTime = SDL_GetTicks();
  pausedTime = 0;
}

void Timer::pause() {
  if ( started != paused ) {
    paused = true;
    pausedTime = SDL_GetTicks() - startTime;
    startTime = 0;
  }
}

void Timer::stop() {
  started = false;
  paused = false;
  startTime = 0;
  pausedTime = 0;
}

void Timer::play() {
  if (started && paused) {
    paused = false;
    startTime = SDL_GetTicks() - pausedTime;
    pausedTime = 0;
  }
}

uint32_t Timer::getTime() {
  uint32_t time = 0;

  if (started) {
    if (paused) time = pausedTime;
    else time = SDL_GetTicks() - startTime;
  }

  return time;
}

