#ifndef OPTIONS_H
#define OPTIONS_H

  #include "textbutton.h"
  #include "texttoggle.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class Options
  {
    public:
      Options(sf::Font& font);
      
      void mouseInput(GameState& state, GameState previousState, sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

      //void toggleFPSDisplay();
      //void toggleVSync();
      void setFPSDisplay(bool state);
      void setVSync(bool state);

      bool fpsDisplaySelected{ false };
      bool vSyncSelected{ false };

    private:
      TextButton backButton{  };
      TextToggle fpsDisplay{  };
      TextToggle vSync{  };
  };

#endif
