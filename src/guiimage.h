#ifndef GUIIMAGE_H
#define GUIIMAGE_H

  #include "guielement.h"
  #include "graphicalresource.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class GUIImage : public GUIElement
  {
    public:
      GUIImage(sf::Vector2f position, GraphicalResource* image, GUIElement* masterElement); 
      GUIImage(GUIElement* masterElement);
      GUIImage() = default;
      
      void setPosition(sf::Vector2f position);
      
      void centerHorizontally();
      void centerVertically();
      void centerInMaster();
      void positionAtTop(int pixels);
      void positionAtRight(int pixels);
      void positionAtBottom(int pixels);
      void positionAtLeft(int pixels);

      GraphicalResource* getImagePointer();
      void setImage(GraphicalResource* image);

      virtual void draw(sf::RenderWindow& window);
      
    private:
      GraphicalResource* image; 

  };

#endif
