#include "maploading.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include <vector>

  #include <iostream>


MapLoading::MapLoading(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    loadMapButton{ font, "load map", sf::Vector2f(1620.0f, 980.0f), 32 },
    saveSelect{ sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1720.0f, 800.0f), 
                50.0 }
{

}

void MapLoading::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
  else if(loadMapButton.isClicked(clickPosition) && saveSelect.getToggles().size() > 0)
  {
    if(saveSelect.getToggles().at(selectedSave).getState())
    {
      state = GameState::game;
    }
    else
    {
      loadMapButton.setPosition(1360.0f, 980.0f);
      loadMapButton.setText("choose save file"); 
    }
  }
  else
  {
    saveSelect.clickInput(clickPosition);

    for(std::size_t id{ 0 }; id < saveSelect.getToggles().size(); ++id)
    {
      if(saveSelect.getToggles().at(id).getState() && id != selectedSave)
      {
        saveSelect.getToggles().at(selectedSave).setState(false);
        selectedSave = id;
      }
    }
  }
}

void MapLoading::holdInput(sf::Vector2i clickPosition)
{
  saveSelect.holdInput(clickPosition);
}

void MapLoading::releaseInput()
{
  saveSelect.releaseInput();
}
      
void MapLoading::scrollInput(double scroll)
{
  saveSelect.scroll(scroll);
}

void MapLoading::run(sf::RenderWindow& window)
{
  if(saveSelect.getToggles().size() > 0 && saveSelect.getToggles().at(selectedSave).getState())
  {
    loadMapButton.setPosition(1620.0f, 980.0f);
    loadMapButton.setText("load map"); 
  }

  saveSelect.draw(window);
  if(saveSelect.getToggles().size() > 0)
  {
    loadMapButton.draw(window);
  }
  backButton.draw(window);
}
      
void MapLoading::loadFilenames(sf::Font& font)
{
  int buttonCounter{ 1 };
  for(auto& file : std::filesystem::directory_iterator("saves/"))
  {
    std::string filename{ file.path().u8string() };
    filename.erase(filename.begin(),
                   filename.begin() + filename.find_first_of("/") + 1);
    filename.erase(filename.begin() + filename.find_last_of("."),
                   filename.end());
    saveSelect.addToggle(font, filename, 
                         sf::Vector2f(100.0f, buttonCounter * 100.0f), 32);
    ++buttonCounter;
  }
}
      
std::string MapLoading::getMapFilename()
{
  return "saves/" + saveSelect.getToggles().at(selectedSave).getString() + ".json";
}
