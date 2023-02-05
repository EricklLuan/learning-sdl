#include "../include/dot.hpp"

Dot::Dot(Sprite texture, Vector2 _position=Vector2()): 
position(_position), velocity(Vector2()), sprite(texture) {

}

void Dot::handleEvent(Input* input) {
  
  if (input->getKeyPressed(SDL_SCANCODE_UP)) velocity.y -= DOT_VEL;
  if (input->getKeyPressed(SDL_SCANCODE_DOWN)) velocity.y += DOT_VEL;
  if (input->getKeyPressed(SDL_SCANCODE_LEFT)) velocity.x -= DOT_VEL;
  if (input->getKeyPressed(SDL_SCANCODE_RIGHT)) velocity.x += DOT_VEL;

  if (input->getKeyRelesead(SDL_SCANCODE_UP)) velocity.y += DOT_VEL;
  if (input->getKeyRelesead(SDL_SCANCODE_DOWN)) velocity.y -= DOT_VEL;
  if (input->getKeyRelesead(SDL_SCANCODE_LEFT)) velocity.x += DOT_VEL;
  if (input->getKeyRelesead(SDL_SCANCODE_RIGHT)) velocity.x -= DOT_VEL;
}

void Dot::move() {
  position.x += velocity.x;

  if (position.x < 0 || position.x + DOT_WIDTH > 1280) {
    position.x -= velocity.x;
  }

  position.y += velocity.y;

  if (position.y < 0 || position.y + DOT_HEIGHT > 960) {
    position.y -= velocity.y;
  }
}

void Dot::render(SDL_Renderer* renderer, Vector2 camera_pos) {
  sprite.render(renderer, Vector2(position.x - camera_pos.x, position.y - camera_pos.y), Vector2());
}

