#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Game::Game()
{
  
}

void Game::mouseInput(GameState& state)
{
  map.switchNodeTerrain();
}

void Game::run(sf::RenderWindow& window, double timeElapsed)
{
  map.selectNodes(sf::Mouse::getPosition(window));

  sf::Vector2i mousePosition{ sf::Mouse::getPosition(window) };
  
  if(mousePosition.x < 10)
  {
    view.move(-100.0 * timeElapsed, 0);
  }
  else if(mousePosition.x > 790)
  {
    view.move(100.0 * timeElapsed, 0);
  }
  
  if(mousePosition.y < 10)
  {
    view.move(0.0, -100.0 * timeElapsed);
  }
  else if(mousePosition.y > 590)
  {
    view.move(0.0, 100.0 * timeElapsed);
  }
  
  window.setView(view);

  window.clear();
  map.draw(window);
  window.display();
}
