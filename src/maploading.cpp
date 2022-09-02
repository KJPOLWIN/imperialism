#include "maploading.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include <vector>


MapLoading::MapLoading(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    loadMapButton{ font, "load map", sf::Vector2f(1620.0f, 980.0f), 32 },
    saveSelect{ sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1720.0f, 800.0f), 
                50.0 }
{
  /*saveSelect.addToggle(font, "test1", sf::Vector2f(100, 100), 32);
  saveSelect.addToggle(font, "test2", sf::Vector2f(100, 200), 32);
  saveSelect.addToggle(font, "test3", sf::Vector2f(100, 300), 32);
  saveSelect.addToggle(font, "test4", sf::Vector2f(100, 400), 32);
  saveSelect.addToggle(font, "test5", sf::Vector2f(100, 500), 32);
  saveSelect.addToggle(font, "test6", sf::Vector2f(100, 600), 32);
  saveSelect.addToggle(font, "test7", sf::Vector2f(100, 700), 32);
  saveSelect.addToggle(font, "test8", sf::Vector2f(100, 800), 32);
  saveSelect.addToggle(font, "test9", sf::Vector2f(100, 900), 32);
  saveSelect.addToggle(font, "test10", sf::Vector2f(100, 1000), 32);
  saveSelect.addToggle(font, "test11", sf::Vector2f(100, 1100), 32);*/

  //Filenames loaded before entering state
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
  saveSelect.draw(window);
  backButton.draw(window);
  loadMapButton.draw(window);
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
