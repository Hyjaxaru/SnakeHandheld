#include <cmath>
//
// vec2.h
//
// 2D Vectors for positions!
//
// Inspired by the vec3 class in the famous book "Raytracing in One Weekend"
// https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class
//

#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
  float x;
  float y;

  Vec2(): x(0), y(0) {}
  Vec2(float x, float y): x(x), y(y) {}

  float magnitude() const {
    return std::sqrt(std::pow(x, 2) * std::pow(y, 2));
  }
};

inline bool operator == (const Vec2& lhs, const Vec2& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline Vec2 operator + (const Vec2& lhs, const Vec2& rhs)
{
  return Vec2(lhs.x + rhs.y, lhs.y + rhs.y);
}

inline Vec2 operator - (const Vec2& lhs, const Vec2& rhs)
{
  return Vec2(lhs.x - rhs.y, lhs.y - rhs.y);
}

#endif