#include "options.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Options::Options(sf::Font& font, GameState& state, GameState& previousState)
{
  backButton.setFont(font);
  backButton.setText("back");
  backButton.setFlag(GUIFlag::clickable);
  backButton.setFunction([&state, &previousState](){
        state = previousState;
      });
  backButton.positionAtBottom(100);
  backButton.positionAtLeft(100);

  fpsDisplay.setFont(font);
  fpsDisplay.setText("FPS display");
  fpsDisplay.setFlag(GUIFlag::togglable);
  fpsDisplay.positionAtTop(100);
  fpsDisplay.positionAtLeft(100);
  
  vSync.setFont(font);
  vSync.setText("vertical sync");
  vSync.setFlag(GUIFlag::togglable);
  vSync.positionDownTo(&fpsDisplay, 50);
  vSync.positionAtLeft(100);
}
      
void Options::mouseInput(sf::Vector2i clickPosition)
{
  backButton.clickInput(clickPosition);
  fpsDisplay.clickInput(clickPosition);
  vSync.clickInput(clickPosition);

  fpsDisplaySelected = fpsDisplay.active;
  vSyncSelected = vSync.active;
}
 
void Options::run(sf::RenderWindow& window)
{
  backButton.draw(window);
  fpsDisplay.draw(window);
  vSync.draw(window);
}
      
void Options::setFPSDisplay(bool state)
{
  fpsDisplay.active = state;
}

void Options::setVSync(bool state)
{
  vSync.active = state;
}
