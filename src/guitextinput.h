#ifndef GUITEXTINPUT
#define GUITEXTINPUT

  #include "guitextlabel.h"
  #include "guielement.h"
  #include <SFML/Graphics.hpp>
  #include <string>

  enum class GUITextInputType
  {
    text,
    numeric
  };

  class GUITextInput : public GUITextLabel
  {
    public:
      GUITextInput(sf::Vector2f position, sf::Font& font, std::string text, unsigned int size, GUIElement* masterElement, int flags);
      GUITextInput(sf::Vector2f position, sf::Font& font, std::string text, 
                   unsigned int size, GUIElement* masterElement);
      GUITextInput(sf::Font& font, std::string text, unsigned int size, 
                   GUIElement* masterElement, int flags);
      GUITextInput(sf::Font& font, std::string text, unsigned int size, 
                   GUIElement* masterElement);
      GUITextInput(unsigned int size, GUIElement* masterElement, int flags);
      GUITextInput(unsigned int size, GUIElement* masterElement);
      GUITextInput() = default;

      virtual ~GUITextInput() {  };

      void setType(GUITextInputType type);

      void clickInput(sf::Vector2i clickPosition);
      void textEnteredInput(char newString);

      void draw(sf::RenderWindow& window) override;

    private:
       GUITextInputType type{ GUITextInputType::text };
  };

#endif


