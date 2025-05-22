#include "CharacterPage.hpp"

CharacterPage::CharacterPage (Game* game)
      : game(game),
        quitButton({100, 100}, {100, 50}, "Quit", game -> getFont()) {}

void CharacterPage::handleInput(sf::RenderWindow &window) {
      while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>()) {
                  window.close();
            }

            if (const auto* mouseButtonPress = event -> getIf<sf::Event::MouseButtonPressed>()) {
                  sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
                  sf::Vector2f mousePos = window.mapPixelToCoords(mousePosPixel);

                  if (quitButton.isClicked(mousePos)) {
                        game -> changeState(std::make_unique<MainPage>(game));
                  }
            }
      }
}

void CharacterPage::update(sf::RenderWindow &window) {

}

void CharacterPage::render(sf::RenderWindow &window) {
      window.clear(sf::Color::Black);
      quitButton.render(window);
      window.display();
}