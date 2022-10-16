#ifndef GRAPHICALRESOURCE_H
#define GRAPHICALRESOURCE_H

  #include <SFML/Graphics.hpp>
  #include <string>

  class GraphicalResource
  {
    public:
      GraphicalResource(std::string filename);
      GraphicalResource() = default;

      void load(std::string filename);
      void setPosition(sf::Vector2f position);
      void setTextureRect(int top, int left, int width, int height);
      void draw(sf::RenderWindow& window);

    private:
      sf::Texture texture{  };
      sf::Sprite sprite{  };
  };

#endif
