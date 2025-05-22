#include "Game.hpp"

Game::Game () : font("./assets/ARIAL.TTF"), window(sf::VideoMode({800, 600}), "Game Window"), currentState(std::make_unique<MainPage>(this)) {
      if (!font.openFromFile("./assets/ARIAL.TTF")) {
            throw std::runtime_error("Error loading font");
      }
}

void Game::run () {
      while (window.isOpen()) {
            currentState -> handleInput(window);
            currentState -> update(window);
            currentState -> render(window);
      }
}

void Game::changeState (std::unique_ptr<GameState> newState) {
      currentState = std::move(newState);
}