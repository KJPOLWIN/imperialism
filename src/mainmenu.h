#ifndef MAINMENU_H
#define MAINMENU_H
  
  #include "gamestate.h"
  #include "textbutton.h"
  #include "guielement.h"
  #include "guitextlabel.h"
  #include <SFML/Graphics.hpp>

  class MainMenu
  {
    public:
      MainMenu(sf::Font& buttonFont, GameState& state);

      void mouseInput(sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

    private:
      GUIElement screen{ sf::Vector2f(1920, 1080), nullptr };
      GUITextLabel title{ 72, &screen };
      GUITextLabel newGameButton{ 40, &screen }; 
      GUITextLabel loadGameButton{ 40, &screen }; 
      GUITextLabel optionsButton{ 40, &screen };
      GUITextLabel creditsButton{ 40, &screen };
      GUITextLabel exitButton{ 40, &screen };
      
  };

#endif
