#pragma once

#include <stdint.h>

class Timer {
private:
  uint32_t startTime;
  uint32_t pausedTime;

  bool paused;
  bool started;

public:
  Timer();

  void start();
  void pause();
  void stop();
  void play();

  uint32_t getTime();

  inline bool isPaused() { return paused && started; }
  inline bool isStarted() { return started; }

};