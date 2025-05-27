#include "MainPage.hpp"

MainPage::MainPage (Game* game) 
    : game(game),
      playButton({200, 400}, {100, 50}, "Play", game -> getFont()),
      characterButton({400, 400}, {100, 50}, "Character", game -> getFont()),
      exitButton({600, 400}, {100 ,50}, "Exit", game -> getFont()) {}

void MainPage::handleInput (sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event -> is<sf::Event::Closed>()) {
            window.close();
        }

        if (event -> is<sf::Event::MouseButtonReleased>()) {
            setMousePos(window);

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
    
}

void MainPage::render (sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    playButton.render(window);
    characterButton.render(window);
    exitButton.render(window);
    
    window.display();
}