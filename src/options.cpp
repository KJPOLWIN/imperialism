#include "options.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Options::Options(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(100, 970), 30 }
{

}
      
void Options::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
}
 
void Options::run(sf::RenderWindow& window)
{
  window.clear();
  backButton.draw(window);
  window.display();
}
