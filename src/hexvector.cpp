#include "hexvector.h"
#include <SFML/Graphics.hpp>

bool operator== (const HexVector& vector1, const HexVector& vector2)
{ 
  return (vector1.q == vector2.q && vector1.r == vector2.r && vector1.s == vector2.s);
}

sf::Vector2i HexVector::toCartesian()
{
  return sf::Vector2i(q + static_cast<int>((r - (r & 1)) / 2), r);
}
