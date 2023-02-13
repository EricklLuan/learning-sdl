#include "../include/dot.hpp"

Dot::Dot(Sprite texture, Vector2 _position=Vector2()): 
position(_position), velocity(Vector2()), sprite(texture) {
  for (int i = 0; i < 19; i++) {
    particles[i] = new Particle(texture, position);
  }
}

Dot::~Dot() {
  for (int i = 0; i < 19; i++) {
    delete particles[i];
  }
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

  if (position.x < 0 || position.x + DOT_WIDTH > 500) {
    position.x -= velocity.x;
  }

  position.y += velocity.y;

  if (position.y < 0 || position.y + DOT_HEIGHT > 500) {
    position.y -= velocity.y;
  }
}

void Dot::render(SDL_Renderer* renderer) {
  for (int i = 0; i < 19; i++) {
    if (particles[i]->isDead()) {
      delete particles[i];
      particles[i] = new Particle(sprite, position);
    }
  }

  for (int i = 0; i < 19; i++) {
    particles[i]->render(renderer);
  }

  sprite.render(renderer, position, Vector2());
}

