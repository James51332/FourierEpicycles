#pragma once

#include <glm/glm.hpp>

namespace fft::complex
{

// ----- General Complex Operations -----

inline glm::vec2 add(const glm::vec2& one, const glm::vec2& two)
{
  return one + two; // same as vector addition
}

inline glm::vec2 sub(const glm::vec2& one, const glm::vec2& two)
{
  return one - two; // same as vector subtraction
}

inline glm::vec2 scale(const glm::vec2& one, float scale)
{
  // (a + bi)c = ac + bci
  return { one.x * scale, one.y * scale };
}

inline glm::vec2 mult(const glm::vec2& one, const glm::vec2& two)
{
  // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
  return { one.x * two.x - one.y * two.y, one.x * two.y + one.y * two.x };
}

// ----- Polar & Rectangular Coordinates -----

inline glm::vec2 exp(float theta)
{
  // e^it = cos(t) + (sin(t))i
  return { glm::cos(theta), glm::sin(theta) };
}

inline glm::vec2 polar(const glm::vec2 rect)
{
  // (r, theta) => (r * cos(theta), r * sin(theta))
  return rect.x * exp(rect.y);
}

inline glm::vec2 rect(const glm::vec2& polar)
{
  // (x, y) => (len(x, y), atan2(y, x))
  return { glm::length(polar), glm::atan(polar.y, polar.x) };
}

}