#ifndef CREDITS_H
#define CREDITS_H

  #include "gamestate.h"
  #include "guielement.h"
  #include "guitextlabel.h"
  #include "constant.h"
  #include <SFML/Graphics.hpp>

  class Credits
  {
    public:
      Credits(sf::Font& font, GameState& state);
      
      void mouseInput(sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

    private:
      GUIElement screen{ sf::Vector2f(1920, 1080), nullptr };

      GUITextLabel backButton{ 32, &screen };

      GUITextLabel title{ 80, &screen };
      GUITextLabel version{ 40, &screen };
      
      GUITextLabel code{ 24, &screen };
      GUITextLabel codeAuthors{ 32, &screen };
      
      GUITextLabel fontLabel{ 24, &screen };
      GUITextLabel fontName{ 32, &screen };
      GUITextLabel fontAuthors{ 32, &screen };
      GUITextLabel fontLicense{ 32, &screen };
      
      GUITextLabel sfml{ 24, &screen };
      GUITextLabel date{ 24, &screen };
      
  };

#endif
