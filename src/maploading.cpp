#include "maploading.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <dirent.h>
//#include <filesystem>
#include <vector>

  #include <iostream>


MapLoading::MapLoading(sf::Font& font, GameState& state)
  : /*backButton{ font, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    loadMapButton{ font, "load map", sf::Vector2f(1620.0f, 980.0f), 32 },*/
    backButton{ font, "back", 32, &screen, GUIFlag::clickable },
    loadMapButton{ font, "load map", 32, &screen, GUIFlag::clickable },
    saveSelect{ sf::Vector2f(1720.0f, 800.0f), 
                &screen, 50.0 }
{
  backButton.positionAtBottom(100);
  backButton.positionAtLeft(100);

  loadMapButton.positionAtBottom(100);
  loadMapButton.positionAtRight(100);

  backButton.setFunction([&state](){
    state = GameState::mainMenu;
      });
  
  loadMapButton.setFunction([&state, this](){
    //if(saveSelect.getToggles().size() > 0)
    if(saveButtons.size() > 0)
    {
      //if(saveSelect.getToggles().at(selectedSave).getState())
      if(saveButtons.at(selectedSave).active)
      {
        state = GameState::game;
      }
      else
      {
        //loadMapButton.setPosition(1360.0f, 980.0f);
        loadMapButton.setText("choose save file"); 
        loadMapButton.positionAtRight(100);
      }
    }
  });

  saveSelect.positionAtTop(100);
  saveSelect.positionAtLeft(100);
}

void MapLoading::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  backButton.clickInput(clickPosition);
  loadMapButton.clickInput(clickPosition);
  saveSelect.clickInput(clickPosition);

  /*for(auto& button : saveButtons)
  {
    button.clickInput(clickPosition);
  }*/

  /*if(backButton.isClicked(clickPosition))
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
      //loadMapButton.setPosition(1360.0f, 980.0f);
      loadMapButton.setText("choose save file"); 
      loadMapButton.positionAtRight(100);
    }
  }
  else
  {*/
    /*saveSelect.clickInput(clickPosition);

    for(std::size_t id{ 0 }; id < saveSelect.getToggles().size(); ++id)
    {
      if(saveSelect.getToggles().at(id).getState() && id != selectedSave)
      {
        saveSelect.getToggles().at(selectedSave).setState(false);
        selectedSave = id;
      }
    }*/
  //}
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
  //std::cout << "run function start\n";

  //if(saveSelect.getToggles().size() > 0 && saveSelect.getToggles().at(selectedSave).getState())
  /*if(saveButtons.size() > 0 && saveButtons.at(selectedSave).active)
  {
    //loadMapButton.setPosition(1620.0f, 980.0f);
    loadMapButton.setText("load map"); 
    loadMapButton.positionAtRight(100);
  }*/
 
  /*std::cout << "checking size\n";
  if(saveButtons.size() > 0)
  {
    std::cout << "checking if active\n";
    //if(saveButtons.at(selectedSave).active)
    {
      //loadMapButton.setPosition(1620.0f, 980.0f);
      //loadMapButton.setText("load map"); 
      //loadMapButton.positionAtRight(100);
    }
  }*/


  /*for(auto& button : saveButtons)
  {
    button.setFont(font);
  }*/


  //std::cout << "drawing save select...";
  saveSelect.draw(window);
  //std::cout << " done\n";
  //if(saveSelect.getToggles().size() > 0)
  if(saveButtons.size() > 0)
  {
    loadMapButton.draw(window);
  }
  backButton.draw(window);
  
  //std::cout << "run function end\n";
}
      
void MapLoading::loadFilenames(sf::Font& font)
{
  //saveSelect.getToggles().clear();
  saveButtons.clear();
  int buttonCounter{ 0 };

  DIR *dir;
  struct dirent *diread;
  if((dir = opendir("./saves")) != nullptr)
  {
    while((diread = readdir(dir)) != nullptr)
    {
      std::string filename{ diread->d_name };
      if(filename.at(0) != '.')
      {
        filename.erase(filename.begin(),
                       filename.begin() + filename.find_first_of("/") + 1);
        filename.erase(filename.begin() + filename.find_last_of("."),
                       filename.end());

        saveButtons.emplace_back(font, filename, 32, &saveSelect, GUIFlag::togglable | GUIFlag::clickable);
        /*saveButtons.back().setFunction([this, buttonCounter](){
              this->selectedSave = buttonCounter;
              for(auto& button : this->saveButtons)
              {
                button.active = false;
              }
              saveButtons.at(selectedSave).active = true;
            });*/
        if(buttonCounter == 0)
        {
          saveButtons.back().positionAtTop(0);
        }
        else
        {
          saveButtons.back().positionDownTo(&saveButtons.at(buttonCounter - 1), 50);
        }

        //saveSelect.addToggle(font, filename, 
        //                     sf::Vector2f(100.0f, buttonCounter * 100.0f), 32);
        ++buttonCounter;
      }
    }
    closedir(dir);

    //For some reason, w/ next 5 lines program crashes
    saveSelect.clearSlaveElements();
    for(auto& button : saveButtons)
    {
      saveSelect.bindElement(&button);
    }
  }
  else
  {
    perror("opendir");
    std::cout << "directory not opened or something\n";
  }

  std::cout << "filenames loaded successfuly\n";
}
      
std::string MapLoading::getMapFilename()
{
  //return "saves/" + saveSelect.getToggles().at(selectedSave).getString() + ".json";
  return "saves/" + saveButtons.at(selectedSave).getText() + ".json";
}
