#include "MainPage.hpp"

MainPage::MainPage (Game* game) 
    : game(game),
      playButton({100, 100}, {100, 50}, "Play", game -> getFont()),
      characterButton({100, 200}, {100, 50}, "Character", game -> getFont()),
      exitButton({100, 300}, {100 ,50}, "Exit", game -> getFont()) {}

void MainPage::handleInput (sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event -> is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mouseButtonPress = event -> getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosPixel);

            if (playButton.isClicked(mousePos)) {
                game -> changeState(std::make_unique<GamePlayPage>(game));
            }

            if (characterButton.isClicked(mousePos)) {
                game -> changeState(std::make_unique<CharacterPage>(game));
            }

            if (exitButton.isClicked(mousePos)) {
                window.close();
            }
        }
    }
}

void MainPage::update (sf::RenderWindow &window) {
    // Update logic can be added here if needed
}

void MainPage::render (sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    playButton.render(window);
    characterButton.render(window);
    exitButton.render(window);
    window.display();
}