#ifndef HEXVECTOR_H
#define HEXVECTOR_H

  #include <SFML/Graphics.hpp>

  class HexVector
  {
    public:
      HexVector(int q, int r, int s)
        : q{ q }, r{ r }, s{ s } {}
      
      HexVector(int x, int y)
        : q{ x - static_cast<int>((y - (y & 1)) / 2) }, 
          r{ y }, 
          s{ -q-r } {}

      HexVector(sf::Vector2i cartesian)
        : q{ cartesian.x - static_cast<int>((cartesian.y - (cartesian.y & 1)) / 2) }, 
          r{ cartesian.y }, 
          s{ -q-r } {}
      
      HexVector() = default;

      friend bool operator== (const HexVector& vector1, const HexVector& vector2);
      friend bool operator!= (const HexVector& vector1, const HexVector& vector2);

      sf::Vector2i toCartesian();
      std::size_t toID(int sizeX);
      HexVector getNW();
      HexVector getNE();
      HexVector getE();
      HexVector getSE();
      HexVector getSW();
      HexVector getW();
      HexVector getNeighbour(int direction);
      bool isInBoundaries(int sizeX, int sizeY);
      bool isNextToNode(HexVector nodeHexCoords);

      int q{ 0 };
      int r{ 0 };
      int s{ 0 };
  };


#endif
