#include "Game.hpp"

Game::Game () : font("./assets/ARIAL.TTF"), window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game Window"), currentState(std::make_unique<MainPage>(this)) {
      if (!font.openFromFile("./assets/ARIAL.TTF")) {
            throw std::runtime_error("Error loading font");
      }
}

void Game::run () {
      DataManager dataManager;
      difficulty = dataManager.getDifficulty();

      sf::Clock clock;

      while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();

            currentState -> handleInput(window);
            currentState -> update(window, deltaTime);
            currentState -> render(window);
      }
}

void Game::changeState (std::unique_ptr<GameState> newState) {
      currentState = std::move(newState);
}