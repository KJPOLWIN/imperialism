#ifndef OPTIONS_H
#define OPTIONS_H

  #include "textbutton.h"
  #include "texttoggle.h"
  #include "guielement.h"
  #include "guitextlabel.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class Options
  {
    public:
      Options(sf::Font& font, GameState& state, GameState& previousState);
      
      void mouseInput(sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

      void setFPSDisplay(bool state);
      void setVSync(bool state);

      bool fpsDisplaySelected{ false };
      bool vSyncSelected{ false };

    private:
      GUIElement screen{ sf::Vector2f(1920, 1080), nullptr };

      GUITextLabel backButton{ 32, &screen };
      GUITextLabel fpsDisplay{ 32, &screen };
      GUITextLabel vSync{ 32, &screen };

  };

#endif
