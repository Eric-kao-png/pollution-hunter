#include "./GamePlayPage.hpp"

GamePlayPage::GamePlayPage(Game* game) 
      : game(game),
        quitButton({100, 100}, {100, 50}, "Quit", game -> getFont()),
        character("Hero", 10, 1, 1, map) {}

void GamePlayPage::handleInput (sf::RenderWindow &window) {
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

                  if (map.isClicked(mousePos)) {
                        character.setTargetPoint(mousePos);
                  }
            }
      }
}

void GamePlayPage::update (sf::RenderWindow &window) {
      map.update();
      character.update();
}

void GamePlayPage::render (sf::RenderWindow &window) {
      window.clear(sf::Color::Black);
      map.render(window);
      character.render(window);
      quitButton.render(window);
      window.display();
}