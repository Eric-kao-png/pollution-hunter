#include "Game.hpp"

Game::Game () : window(sf::VideoMode({800, 600}), "Game Window"), currentState(std::make_unique<MainPage>(this)), font("./assets/ARIAL.TTF") {
}

void Game::run () {
      while (window.isOpen()) {
            currentState -> handleInput(window);
            currentState -> update(window);
            window.clear();
            currentState -> render(window);
            window.display();
      }
}

void Game::changeState (std::unique_ptr<GameState> newState) {
      currentState = std::move(newState);
}