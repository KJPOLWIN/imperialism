#include "options.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Options::Options(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(100, 968), 32 },
    fpsDisplay{ font, "FPS display", sf::Vector2f(100, 100), 32 },
    vSync{ font, "vertical sync", sf::Vector2f(100, 150), 32 }
{

}
      
void Options::mouseInput(GameState& state, GameState previousState, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = previousState;
  }
  else
  {
    fpsDisplay.clickInput(clickPosition);
    vSync.clickInput(clickPosition);
  }
  /*else if(fpsDisplay.isClicked(clickPosition))
  {
    fpsDisplaySelected = !fpsDisplaySelected;
  }
  else if(vSync.isClicked(clickPosition))
  {
    vSyncSelected = !vSyncSelected;
  }*/

  fpsDisplaySelected = fpsDisplay.getState();
  vSyncSelected = vSync.getState();
}
 
void Options::run(sf::RenderWindow& window)
{
  backButton.draw(window);
  fpsDisplay.draw(window);
  vSync.draw(window);
}
      
/*void Options::toggleFPSDisplay()
{
  fpsDisplay.toggle();
}

void Options::toggleVSync()
{
  vSync.toggle();
}*/

void Options::setFPSDisplay(bool state)
{
  fpsDisplay.setState(state);
}

void Options::setVSync(bool state)
{
  vSync.setState(state);
}
