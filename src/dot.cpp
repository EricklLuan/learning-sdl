#include "../include/dot.hpp"

Dot::Dot(Sprite texture, Vector2 _position=Vector2()): 
position(_position), velocity(Vector2()), sprite(texture) {

  collider.w = DOT_WIDTH;
  collider.h = DOT_HEIGHT;
  collider.x = _position.x;
  collider.y = _position.y;
  
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

void Dot::move(SDL_Rect& wall) {
  position.x += velocity.x;
  collider.x = position.x;

  if (position.x < 0 || position.x + DOT_WIDTH > 500 || checkCollision(&collider, &wall)) {
    position.x -= velocity.x;
    collider.x = position.x;
  }

  position.y += velocity.y;
  collider.y = position.y;

  if (position.y < 0 || position.y + DOT_HEIGHT > 500 || checkCollision(&collider, &wall)) {
    position.y -= velocity.y;
    collider.y = position.y;
  }
}

void Dot::render(SDL_Renderer* renderer) {
  sprite.render(renderer, position, Vector2());
}

bool Dot::checkCollision(SDL_Rect* a, SDL_Rect* b) {
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