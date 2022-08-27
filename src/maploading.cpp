#include "maploading.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>


MapLoading::MapLoading(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    loadMapButton{ font, "load map", sf::Vector2f(1620.0f, 980.0f), 32 }
{

}

void MapLoading::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
  else if(loadMapButton.isClicked(clickPosition))
  {
    state = GameState::game;
  }
}

void MapLoading::run(sf::RenderWindow& window)
{
  backButton.draw(window);
  loadMapButton.draw(window);
}
      
std::string MapLoading::getMapFilename()
{
  return "test.json";
}
