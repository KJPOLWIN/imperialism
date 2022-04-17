#ifndef HEXVECTOR_H
#define HEXVECTOR_H

  #include <SFML/Graphics.hpp>

  class HexVector
  {
    public:
      HexVector(int q, int r, int s)
        : q{ q }, r{ r }, s{ s } {}
      
      HexVector(int x, int y)
        : q{ x - static_cast<int>((y - (y & 1)) / 2) }, r{ y }, s{ -q-r } {}
      
      HexVector() = default;

      friend bool operator== (const HexVector& vector1, const HexVector& vector2);

      sf::Vector2i toCartesian();

      int q{ 0 };
      int r{ 0 };
      int s{ 0 };
  };


#endif
