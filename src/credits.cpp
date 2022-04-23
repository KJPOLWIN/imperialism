#include "credits.h"
#include "textbutton.h"
#include "gamestate.h"
#include "gui.h"
#include <SFML/Graphics.hpp>

Credits::Credits(sf::Font& font)
  : backButton{ font, "back", sf::Vector2f(100, 970), 30 },
    title{ "imperialism", font, 76 },
    version{ "early development edition", font, 36 },
    code{ "Code and graphics", font, 24 },
    codeAuthors{ "POLWIN", font, 32 },
    fontLabel{ "Font", font, 24 },
    fontName{ "Press Start 2P", font, 32 },
    fontAuthors{ "made by CodeMan38", font, 32 },
    fontLicense{ "licensed under Open Font License", font, 32 },
    sfml{ "Made with SFML", font, 26 },
    date{ "2022", font, 26 }
{
  title.setPosition(0, 75);
  GUI::centerTextInField(title, positioningField);

  version.setPosition(0, 175);
  GUI::centerTextInField(version, positioningField);

  code.setPosition(0, 400);
  GUI::centerTextInField(code, positioningField);

  codeAuthors.setPosition(0, 450);
  GUI::centerTextInField(codeAuthors, positioningField);
  
  fontLabel.setPosition(0, 600);
  GUI::centerTextInField(fontLabel, positioningField);
  
  fontName.setPosition(0, 650);
  GUI::centerTextInField(fontName, positioningField);

  fontAuthors.setPosition(0, 700);
  GUI::centerTextInField(fontAuthors, positioningField);

  fontLicense.setPosition(0, 750);
  GUI::centerTextInField(fontLicense, positioningField);
  
  sfml.setPosition(0, 950);
  GUI::centerTextInField(sfml, positioningField);

  date.setPosition(0, 1000);
  GUI::centerTextInField(date, positioningField);
}
      
void Credits::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
}
 
void Credits::run(sf::RenderWindow& window)
{
  backButton.draw(window);
  window.draw(title);
  window.draw(version);
  window.draw(code);
  window.draw(codeAuthors);
  window.draw(fontLabel);
  window.draw(fontName);
  window.draw(fontAuthors);
  window.draw(fontLicense);
  window.draw(sfml);
  window.draw(date);
}
