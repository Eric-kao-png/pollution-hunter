#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "../GameState.hpp"
#include "../Game.hpp"
#include "../entities/Button.hpp"
#include "./CharacterPage.hpp"
#include "./GamePlayPage.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Game;

class MainPage : public GameState {
      private:

      Game* game;

      Button playButton;
      Button characterButton;
      Button exitButton;

      public:

      MainPage(Game* game);

      void handleInput(sf::RenderWindow &window) override;
      void update(sf::RenderWindow &window) override;
      void render(sf::RenderWindow &window) override;
      ~MainPage () override = default;
};

#endif // MAINPAGE_H