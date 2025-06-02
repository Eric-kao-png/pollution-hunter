#include "CharacterPage.hpp"

CharacterPage::CharacterPage (Game* game)
      : game(game),
        quitButton({CHARACTER_PAGE_WIDTH / 2.f, CHARACTER_PAGE_HEIGHT * 6 / 8}, {500, 50}, "Quit", game -> getFont()) {}

void CharacterPage::handleInput(sf::RenderWindow &window) {
      while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>()) {
                  window.close();
            }

            if (event -> is<sf::Event::MouseButtonReleased>()) {
                  setMousePos(window, window.getDefaultView());

                  if (quitButton.isClicked(mousePos)) {
                        game -> changeState(std::make_unique<MainPage>(game));
                  }
            }
      }
}

void CharacterPage::update(sf::RenderWindow &window, float deltaTime) {
      
}

void CharacterPage::render(sf::RenderWindow &window) {
      window.clear(sf::Color::Black);

      quitButton.render(window);
      
      window.display();
}