#include "options.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Options::Options(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(100, 968), 32 },
    fpsDisplay{ font, "FPS display", sf::Vector2f(100, 100), 32 }
{

}
      
void Options::mouseInput(GameState& state, GameState previousState, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = previousState;
  }
  else if(fpsDisplay.isClicked(clickPosition))
  {

  }
}
 
void Options::run(sf::RenderWindow& window)
{
  window.clear();
  backButton.draw(window);
  fpsDisplay.draw(window);
  window.display();
}
