#include "credits.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Credits::Credits(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(100, 970), 30 }
{

}
      
void Credits::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
}
 
void Credits::run(sf::RenderWindow& window)
{
  window.clear();
  backButton.draw(window);
  window.display();
}
