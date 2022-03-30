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
  map.selectNodes(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

  sf::Vector2i mousePosition{ sf::Mouse::getPosition(window) };
  double scrollSpeed{ 500.0 };

  if(mousePosition.x < 10)
  {
    view.move(-scrollSpeed * timeElapsed, 0);
  }
  else if(mousePosition.x > 790)
  {
    view.move(scrollSpeed * timeElapsed, 0);
  }
  
  if(mousePosition.y < 10)
  {
    view.move(0.0, -scrollSpeed * timeElapsed);
  }
  else if(mousePosition.y > 590)
  {
    view.move(0.0, scrollSpeed * timeElapsed);
  }
  
  window.setView(view);

  window.clear();
  map.draw(window);
  window.display();
}

void Game::regenerateMap(int width, int height)
{
  map.regenerate(width, height);
}
