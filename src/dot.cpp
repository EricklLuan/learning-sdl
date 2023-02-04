#include "../include/dot.hpp"

Dot::Dot(Sprite texture, Vector2 _position=Vector2()): 
position(_position), velocity(Vector2()), sprite(texture) {

  colliders.resize(11);

  colliders[ 0 ].w = 6;
  colliders[ 0 ].h = 1;

  colliders[ 1 ].w = 10;
  colliders[ 1 ].h = 1;

  colliders[ 2 ].w = 14;
  colliders[ 2 ].h = 1;

  colliders[ 3 ].w = 16;
  colliders[ 3 ].h = 2;

  colliders[ 4 ].w = 18;
  colliders[ 4 ].h = 2;

  colliders[ 5 ].w = 20;
  colliders[ 5 ].h = 6;

  colliders[ 6 ].w = 18;
  colliders[ 6 ].h = 2;

  colliders[ 7 ].w = 16;
  colliders[ 7 ].h = 2;

  colliders[ 8 ].w = 14;
  colliders[ 8 ].h = 1;

  colliders[ 9 ].w = 10;
  colliders[ 9 ].h = 1;

  colliders[ 10 ].w = 6;
  colliders[ 10 ].h = 1;

  shiftColliders();
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

void Dot::move(std::vector<SDL_Rect>& oColliders) {
  position.x += velocity.x;
  shiftColliders();

  if (position.x < 0 || position.x + DOT_WIDTH > 500 || checkCollision(colliders, oColliders)) {
    position.x -= velocity.x;
    shiftColliders();
  }

  position.y += velocity.y;
  shiftColliders();

  if (position.y < 0 || position.y + DOT_HEIGHT > 500 || checkCollision(colliders, oColliders)) {
    position.y -= velocity.y;
    shiftColliders();
  }
}

void Dot::render(SDL_Renderer* renderer) {
  sprite.render(renderer, position, Vector2());
}

bool Dot::checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b) {

  for (int i=0; i < a.size(); i++) {
    int leftA = a[i].x;
    int rightA = a[i].x + a[i].w;
    int topA = a[i].y;
    int bottomA = a[i].y + a[i].h;

    for (int j=0; j < b.size(); j++) {
      int leftB = b[j].x;
      int rightB = b[j].x + b[j].w;
      int topB = b[j].y;
      int bottomB = b[j].y + b[j].h;

      if ( ( (bottomA <= topB) || (topA >= bottomB) || (leftA >= rightB) || (rightA <= leftB) ) == false ) {
        return true;
      }
    }
  }

  return false;
}

void Dot::shiftColliders() {
  int r = 0;
  for(int i = 0; i < colliders.size(); i++) {
    colliders[i].x = position.x + (DOT_WIDTH - colliders[i].w/2);
    colliders[i].y = position.y + r;

    r += colliders[i].h;
  }
}
