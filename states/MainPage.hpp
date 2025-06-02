#ifndef MAINPAGE_HPP
#define MAINPAGE_HPP

#include "../GameState.hpp"
#include "../Game.hpp"
#include "../entities/Button.hpp"
#include "./CharacterPage.hpp"
#include "./GamePlayPage.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr int MAINPAGE_WIDTH = 128 * 6;
constexpr int MAINPAGE_HEIGHT = 128 * 6;

class Game;

class MainPage : public GameState {
      private:

      Game* game;

      // buttons
      Button playButton;
      Button characterButton;
      Button exitButton;

      public:

      MainPage(Game* game);

      void handleInput(sf::RenderWindow &window) override;
      void update(sf::RenderWindow &window, float deltaTime) override;
      void render(sf::RenderWindow &window) override;
      ~MainPage () override = default;
};

#endif // MAINPAGE_HPP