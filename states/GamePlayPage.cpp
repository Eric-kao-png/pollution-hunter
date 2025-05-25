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

            sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
            mousePos = window.mapPixelToCoords(mousePosPixel);

            if (const auto* mouseButtonPress = event -> getIf<sf::Event::MouseButtonPressed>()) {

                  if (quitButton.isClicked(mousePos)) {
                        game -> changeState(std::make_unique<MainPage>(game));
                  }

                  if (map.isClicked(mousePos)) {
                        character.setTargetPoint(mousePos);
                  }
            }

            if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {

                  if (keyPressed -> code == sf::Keyboard::Key::A)  {
                        character.setIsAttacking(true);
                  }
            }
            if (const auto* keyReleased = event -> getIf<sf::Event::KeyReleased>()) {

                  if (keyReleased -> code == sf::Keyboard::Key::A)  {
                        character.setIsAttacking(false);
                  }
            }
      }
}

void GamePlayPage::update (sf::RenderWindow &window) {
      map.update();
      character.update(mousePos);
}

void GamePlayPage::render (sf::RenderWindow &window) {
      window.clear(sf::Color::Black);
      map.render(window);
      character.render(window);
      quitButton.render(window);
      window.display();
}