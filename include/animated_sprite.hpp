#pragma once

#include "./sprite.hpp"
#include "./vector2.hpp"

struct SDL_Texture;
struct SDL_Renderer;

class AnimatedSprite: private Sprite {
private:
  int maxFrames;
  int actualFrame = 0;
public:

  AnimatedSprite(SDL_Texture* texture, Vector2 nSize, int maxFrames);

  void render(SDL_Renderer* renderer, Vector2 position, int vertical=0, int fps=12);
  
  inline Vector2 getActualFrame() { return actualFrame; }
  inline void setActualFrame(int frame) { actualFrame = frame; }

};