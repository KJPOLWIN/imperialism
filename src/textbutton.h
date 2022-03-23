#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

  #include <SFML/Graphics.hpp>
  #include <string>

  class TextButton
  {
    public:
      TextButton(sf::Font& font, std::string text, sf::Vector2f position);
      TextButton();

      void draw(sf::RenderWindow& targetWindow);

    private:
      sf::Text text{  };

  };

#endif
