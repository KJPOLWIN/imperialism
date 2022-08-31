#ifndef MAPLOADING_H
#define MAPLOADING_H

  #include "textbutton.h"
  #include "texttoggle.h"
  #include "scrollarea.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class MapLoading
  {
    public:
      MapLoading(sf::Font& font);

      void mouseInput(GameState& state, sf::Vector2i clickPosition);
      void holdInput(sf::Vector2i clickPosition);
      void scrollInput(double scroll);
      void releaseInput();

      void run(sf::RenderWindow& window);

      std::string getMapFilename();

    private:
      TextButton backButton{  };
      TextButton loadMapButton{  };
      
      ScrollArea saveSelect{  };

      int selectedSave{ 0 };
  };

#endif
