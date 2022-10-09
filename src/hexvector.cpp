#include "hexvector.h"
#include <SFML/Graphics.hpp>

bool operator== (const HexVector& vector1, const HexVector& vector2)
{ 
  return (vector1.q == vector2.q && vector1.r == vector2.r && vector1.s == vector2.s);
}

bool operator!= (const HexVector& vector1, const HexVector& vector2)
{ 
  return (vector1.q != vector2.q || vector1.r != vector2.r || vector1.s != vector2.s);
}
      
HexVector operator+ (const HexVector& vector1, const HexVector& vector2)
{
  return HexVector(vector1.q + vector2.q, vector1.r + vector2.r, vector1.s + vector2.s);
}

sf::Vector2i HexVector::toCartesian()
{
  return sf::Vector2i(q + static_cast<int>((r - (r & 1)) / 2), r);
}
      
std::size_t HexVector::toID(int sizeX)
{
  return static_cast<std::size_t>(toCartesian().y * sizeX
                                + toCartesian().x);
}

HexVector HexVector::getNW()
{
  return HexVector(q, r - 1, s + 1);
}

HexVector HexVector::getNE()
{
  return HexVector(q + 1, r - 1, s);
}

HexVector HexVector::getE()
{
  return HexVector(q + 1, r, s - 1);
}

HexVector HexVector::getSE()
{
  return HexVector(q, r + 1, s - 1);
}

HexVector HexVector::getSW()
{
  return HexVector(q - 1, r + 1, s);
}

HexVector HexVector::getW()
{
  return HexVector(q - 1, r, s + 1);
}
      
HexVector HexVector::getNeighbour(int direction)
{
  switch(direction)
  {
    case 0:
      return getNW();
    break;
    
    case 1:
      return getNE();
    break;
    
    case 2:
      return getE();
    break;
    
    case 3:
      return getSE();
    break;
    
    case 4:
      return getSW();
    break;
    
    case 5:
      return getW();
    break;
  }

  return HexVector();
}
      
bool HexVector::isInBoundaries(int sizeX, int sizeY)
{
  return (toCartesian().x >= 0 && toCartesian().x < sizeX
       && toCartesian().y >= 0 && toCartesian().y < sizeY);
}
      
bool HexVector::isNextToNode(HexVector nodeHexCoords)
{
  return (getNW() == nodeHexCoords
       || getNE() == nodeHexCoords
       || getE()  == nodeHexCoords
       || getSE() == nodeHexCoords
       || getSW() == nodeHexCoords
       || getW()  == nodeHexCoords);
}
