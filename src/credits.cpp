#include "credits.h"
#include "textbutton.h"
#include "gamestate.h"
#include "gui.h"
#include <SFML/Graphics.hpp>

Credits::Credits(sf::Font& font, GameState& state)
{
  backButton.setFont(font);
  backButton.setText("back");
  backButton.positionAtBottom(100);
  backButton.positionAtLeft(100);
  backButton.setFlag(GUIFlag::clickable);
  backButton.setFunction([&state](){
               state = GameState::mainMenu;
                                   });

  title.setFont(font);
  title.setText("imperialism");
  title.positionAtTop(75);
  title.centerHorizontally();

  version.setFont(font);
  version.setText("early development edition");
  version.positionDownTo(&title, 20);
  version.centerHorizontally();

  code.setFont(font);
  code.setText("Code and graphics");
  code.positionDownTo(&version, 100);
  code.centerHorizontally();

  codeAuthors.setFont(font);
  codeAuthors.setText("POLWIN");
  codeAuthors.positionDownTo(&code, 15);
  codeAuthors.centerHorizontally();

  fontLabel.setFont(font);
  fontLabel.setText("Font");
  fontLabel.positionDownTo(&codeAuthors, 150);
  fontLabel.centerHorizontally();

  fontName.setFont(font);
  fontName.setText("Press Start 2P");
  fontName.positionDownTo(&fontLabel, 15);
  fontName.centerHorizontally();

  fontAuthors.setFont(font);
  fontAuthors.setText("made by CodeMan38");
  fontAuthors.positionDownTo(&fontName, 15);
  fontAuthors.centerHorizontally();

  fontLicense.setFont(font);
  fontLicense.setText("licensed under Open Font License");
  fontLicense.positionDownTo(&fontAuthors, 15);
  fontLicense.centerHorizontally();

  date.setFont(font);
  date.setText("2022");
  date.positionAtBottom(100);
  date.centerHorizontally();
  
  sfml.setFont(font);
  sfml.setText("Made with SFML");
  sfml.positionUpTo(&date, 15);
  sfml.centerHorizontally();
}
      
void Credits::mouseInput(sf::Vector2i clickPosition)
{
  screen.clickInput(clickPosition);
}
 
void Credits::run(sf::RenderWindow& window)
{
  backButton.draw(window);
  title.draw(window);
  version.draw(window);
  code.draw(window);
  codeAuthors.draw(window);
  fontLabel.draw(window);
  fontName.draw(window);
  fontAuthors.draw(window);
  fontLicense.draw(window);
  sfml.draw(window);
  date.draw(window);
}
