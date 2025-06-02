#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "./GameState.hpp"
#include "./states/MainPage.hpp"
#include "./states/CharacterPage.hpp"
#include "DataManager.hpp"

constexpr int WINDOW_WIDTH = 128 * 6;
constexpr int WINDOW_HEIGHT = 128 * 6;

class MainPage;

class Game {
      private:

      sf::Font font;
      sf::RenderWindow window;
      std::unique_ptr<GameState> currentState;
      Difficulty difficulty;

      public:

      Game ();

      const sf::Font& getFont () const { return font; }

      void run ();
      void changeState (std::unique_ptr<GameState> newState);
      Difficulty getdifficulty () const { return difficulty; }
};

#endif // GAME_HPP