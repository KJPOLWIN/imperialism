#include "maploading.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>


MapLoading::MapLoading(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    loadMapButton{ font, "load map", sf::Vector2f(1620.0f, 980.0f), 32 },
    saveSelect{ sf::Vector2f(100.0f, 100.0f), 500.0f }
{
  saveButtons.emplace_back(font, "test1", sf::Vector2f(100, 100), 32);
  saveButtons.emplace_back(font, "test2", sf::Vector2f(100, 200), 32);
  saveButtons.emplace_back(font, "test3", sf::Vector2f(100, 300), 32);
  saveButtons.emplace_back(font, "test4", sf::Vector2f(100, 400), 32);
  saveButtons.emplace_back(font, "test5", sf::Vector2f(100, 500), 32);
  saveButtons.emplace_back(font, "test6", sf::Vector2f(100, 600), 32);
  saveButtons.emplace_back(font, "test7", sf::Vector2f(100, 700), 32);
  saveButtons.emplace_back(font, "test8", sf::Vector2f(100, 800), 32);
  saveButtons.emplace_back(font, "test9", sf::Vector2f(100, 900), 32);
  saveButtons.emplace_back(font, "test10", sf::Vector2f(100, 1000), 32);
  saveButtons.emplace_back(font, "test11", sf::Vector2f(100, 1100), 32);

  for(std::size_t id{ 0 }; id < saveButtons.size(); ++id)
  {
    saveSelect.bindButton(saveButtons.at(id), font);
  }
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
  else
  {
    for(std::size_t id{ 0 }; id < saveButtons.size(); ++id)
    {
      if(saveButtons.at(id).isClicked(clickPosition))
      {
        selectedSave = id;
        break;
      }
    }
  }

  for(std::size_t id{ 0 }; id < saveButtons.size(); ++id)
  {
    saveButtons.at(id).setState(id == selectedSave);
  } 
}
      
void MapLoading::scrollInput(double scroll)
{
  saveSelect.scroll(scroll);
}

void MapLoading::run(sf::RenderWindow& window)
{
  backButton.draw(window);
  loadMapButton.draw(window);
  saveSelect.draw(window);
}
      
std::string MapLoading::getMapFilename()
{
  return "test.json";
}
