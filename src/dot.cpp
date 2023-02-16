#include "../include/dot.hpp"

Dot::Dot(Sprite texture, Vector2 _position=Vector2()): 
position(_position), velocity(Vector2()), sprite(texture) {
  
}

Dot::~Dot() {
  
}

void Dot::handleEvent(Input* input) {
  
  if (input->getKeyHeld(SDL_SCANCODE_UP)) velocity.y = -DOT_VEL;
  else if (input->getKeyHeld(SDL_SCANCODE_DOWN)) velocity.y = DOT_VEL;
  else velocity.y = 0;


  if (input->getKeyHeld(SDL_SCANCODE_LEFT)) velocity.x = -DOT_VEL;
  else if (input->getKeyHeld(SDL_SCANCODE_RIGHT)) velocity.x = DOT_VEL;
  else velocity.x = 0;

}

void Dot::move(float delta) {
  position.x += velocity.x * delta;

  if ((position.x < 0)) {
    position.x = 0;
  } else if ((position.x + DOT_WIDTH > 1280)) {
    position.x = 1280 - DOT_WIDTH;
  }

  position.y += velocity.y * delta;

  if ((position.y < 0)) {
    position.y = 0;
  } else if ((position.y + DOT_HEIGHT > 960)) {
    position.y = 960 - DOT_HEIGHT;
  }
}

void Dot::render(SDL_Renderer* renderer, Vector2 camera_positon) {
  Vector2 pPosition = Vector2(
    position.x - camera_positon.x,
    position.y - camera_positon.y
  );

  sprite.render(renderer, pPosition, Vector2());
}

