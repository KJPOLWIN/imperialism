#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Game::Game()
{
  shadeTexture.loadFromFile("texture/shade.png");
  shade.setTexture(shadeTexture); 
}

void Game::mouseInput(GameState& state)
{
  map.switchNodeTerrain();
}

void Game::switchPause()
{
  paused = !paused;
}

void Game::run(sf::RenderWindow& window, double timeElapsed)
{
  map.selectNodes(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

  sf::Vector2i mousePosition{ sf::Mouse::getPosition(window) };
  double scrollSpeed{ 500.0 };
  
  if(!paused)
  {
    if(mousePosition.x < 10)
    {
      mapView.move(-scrollSpeed * timeElapsed, 0);
    }
    else if(mousePosition.x > 790)
    {
      mapView.move(scrollSpeed * timeElapsed, 0);
    }
  
    if(mousePosition.y < 10)
    {
      mapView.move(0.0, -scrollSpeed * timeElapsed);
    }
    else if(mousePosition.y > 590)
    {
      mapView.move(0.0, scrollSpeed * timeElapsed);
    }
  }
  
  window.clear();
  
  window.setView(mapView);
  map.draw(window);
  
  window.setView(guiView);
  if(paused)
  {
    window.draw(shade);
  
  }
  window.display();
}

void Game::regenerateMap(int width, int height, int landmassCount, int landmassSize)
{
  map.regenerate(width, height, landmassCount, landmassSize);
}
