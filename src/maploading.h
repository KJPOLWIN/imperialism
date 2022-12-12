#ifndef MAPLOADING_H
#define MAPLOADING_H

  #include "textbutton.h"
  #include "texttoggle.h"
  #include "scrollarea.h"
  #include "guielement.h"
  #include "guitextlabel.h"
  #include "guiscrollarea.h"
  #include "gamestate.h"
  #include "constant.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class MapLoading
  {
    public:
      MapLoading(sf::Font& font, GameState& state);

      void mouseInput(GameState& state, sf::Vector2i clickPosition);
      void holdInput(sf::Vector2i clickPosition);
      void scrollInput(double scroll);
      void releaseInput();

      //void run(sf::RenderWindow& window);
      void run(sf::RenderWindow& window);

      void loadFilenames(sf::Font& font);

      std::string getMapFilename();

    private:
      //TextButton backButton{  };
      //TextButton loadMapButton{  };
      
      GUIElement screen{ sf::Vector2f(Constant::windowWidth, Constant::windowHeight), nullptr };

      GUITextLabel backButton{  };
      GUITextLabel loadMapButton{  };
      
      //ScrollArea saveSelect{  };
      GUIScrollArea saveSelect{  };
      std::vector<GUITextLabel> saveButtons{  };

      std::size_t selectedSave{ 0 };
  };

#endif
