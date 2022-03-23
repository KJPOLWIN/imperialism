#include "mainmenu.h"
#include "gamestate.h"
#include "textbutton.h"
#include <SFML/Graphics.hpp>

MainMenu::MainMenu(sf::Font& buttonFont)
  : startButton(buttonFont, "start", sf::Vector2f(50.0f, 50.0f))
{
  
}

void MainMenu::mouseInput(GameState& state)
{
  
}

void MainMenu::run(sf::RenderWindow& window)
{
  startButton.draw(window);
}
