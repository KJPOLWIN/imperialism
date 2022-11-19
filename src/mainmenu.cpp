#include "mainmenu.h"
#include "gamestate.h"
#include "textbutton.h"
#include <SFML/Graphics.hpp>

  #include <iostream>


MainMenu::MainMenu(sf::Font& buttonFont, GameState& state)
{
  title.setFont(buttonFont);
  title.setText("imperialism");
  title.positionAtTop(100);
  title.positionAtLeft(100);

  newGameButton.setFont(buttonFont);
  newGameButton.setText("new game");
  newGameButton.positionDownTo(&title, 250);
  newGameButton.positionAtLeft(100);
  newGameButton.setFlag(GUIFlag::clickable);
  newGameButton.setFunction([&state](){
                    state = GameState::gameSettings;
                                      });
  
  loadGameButton.setFont(buttonFont);
  loadGameButton.setText("load game");
  loadGameButton.positionDownTo(&newGameButton, 50);
  loadGameButton.positionAtLeft(100);
  loadGameButton.setFlag(GUIFlag::clickable);
  loadGameButton.setFunction([&state](){
                    state = GameState::mapLoading;
                                      });
  
  optionsButton.setFont(buttonFont);
  optionsButton.setText("options");
  optionsButton.positionDownTo(&loadGameButton, 50);
  optionsButton.positionAtLeft(100);
  optionsButton.setFlag(GUIFlag::clickable);
  optionsButton.setFunction([&state](){
                    state = GameState::options;
                                      });
  
  creditsButton.setFont(buttonFont);
  creditsButton.setText("credits");
  creditsButton.positionDownTo(&optionsButton, 50);
  creditsButton.positionAtLeft(100);
  creditsButton.setFlag(GUIFlag::clickable);
  creditsButton.setFunction([&state](){
                    state = GameState::credits;
                                      });
  
  exitButton.setFont(buttonFont);
  exitButton.setText("exit");
  exitButton.positionDownTo(&creditsButton, 50);
  exitButton.positionAtLeft(100);
  exitButton.setFlag(GUIFlag::clickable);
  exitButton.setFunction([&state](){
                    state = GameState::exit;
                                      });
}

void MainMenu::mouseInput(sf::Vector2i clickPosition)
{
  screen.clickInput(clickPosition);
}

void MainMenu::run(sf::RenderWindow& window)
{
  title.draw(window);
  newGameButton.draw(window);
  loadGameButton.draw(window);
  optionsButton.draw(window);
  creditsButton.draw(window);
  exitButton.draw(window);
}
