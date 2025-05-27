#include "CharacterPage.hpp"

CharacterPage::CharacterPage (Game* game)
      : game(game),
        quitButton({600, 400}, {100, 50}, "Quit", game -> getFont()) {}

void CharacterPage::handleInput(sf::RenderWindow &window) {
      while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>()) {
                  window.close();
            }

            if (event -> is<sf::Event::MouseButtonReleased>()) {
                  setMousePos(window);

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