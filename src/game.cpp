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

void Game::run(sf::RenderWindow& window)
{
  map.selectNodes(sf::Mouse::getPosition(window));

  window.clear();
  map.draw(window);
  window.display();
}
