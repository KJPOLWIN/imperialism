#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

  #include <SFML/Graphics.hpp>
  #include <string>
  #include <functional>

  class TextButton
  {
    public:
      TextButton(sf::Font& font, std::string text, 
                 sf::Vector2f position, unsigned int size);
      TextButton(sf::Font& font, std::string text, 
                 sf::Vector2f position, unsigned int size, 
                 std::function<void()> function);
      TextButton();
      
      bool isClicked(sf::Vector2i clickPosition);
      void draw(sf::RenderWindow& targetWindow);

      void setPosition(sf::Vector2f newPosition);
      void setPosition(double x, double y);
      sf::Vector2f getPosition();

      sf::Vector2f getSize();

      std::string getText();
      void setText(std::string newText);

      void setFont(sf::Font& font);

      void setFunction(std::function<void()>& func);

    private:
      sf::Text text{  };
      std::function<void()> function{ 
        [](){}
      };

  };

#endif
