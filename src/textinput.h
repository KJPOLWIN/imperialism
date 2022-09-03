#ifndef TEXTINPUT_H
#define TEXTINPUT_H

  #include <SFML/Graphics.hpp>
  #include <string>

  enum class InputType
  {
    numeric,
    text
  };

  class TextInput
  {
    public:
      TextInput(sf::Font& font, std::string string, unsigned int size, 
                sf::Vector2f position, InputType type = InputType::numeric);
      TextInput() = default;
      
      bool clickInput(sf::Vector2i clickPosition);
      void updateText(char newString);
      std::string getText();
      void setText(std::string text);
      void draw(sf::RenderWindow& window);
      bool isActive(); 
      void deactivate();
      void activate();

    private:
      
      sf::Text text{  };
      sf::RectangleShape background{  };
      InputType type{ InputType::numeric }; 

      bool active{ false };
  };

#endif
