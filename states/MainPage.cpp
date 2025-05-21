#include "MainPage.hpp"

MainPage::MainPage (Game* game) : game(game) {

}

void MainPage::handleInput (sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event -> is<sf::Event::Closed>()) {
            window.close();
        }

        if (event -> is<sf::Event::MouseButtonReleased>()) {
            
        }
    }
}

void MainPage::update (sf::RenderWindow &window) {
    std::cout << "test1";
}

void MainPage::render (sf::RenderWindow &window) {
    std::cout << "test2";
}