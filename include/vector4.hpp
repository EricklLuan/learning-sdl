#pragma once

struct Vector4 {
  float x, r;
  float y, g;
  float z, b;
  float w, a;

  Vector4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=0.0f):
  x(_x), y(_y), z(_z), w(_w), r(_x), g(_y), b(_z), a(_w) {}

  inline Vector4 white() { return Vector4(255, 255, 255, 255); }
  inline Vector4 black() { return Vector4(0, 0, 0, 255); }
};
