#include "../include/particle.hpp"

Particle::Particle(Sprite mtexture, Vector2 start_positon): texture(mtexture) {
  position.x = start_positon.x + (rand() % 25);
  position.y = start_positon.y + (rand() % 25);

  frame = rand()  % 5;

}

void Particle::render(SDL_Renderer* renderer) {
  texture.render(renderer, position, Vector2());
  frame++;
}

bool Particle::isDead() {
  return frame>10;
}
