#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "./GameState.hpp"
#include "./states/MainPage.hpp"
#include "./states/CharacterPage.hpp"

class MainPage;

class Game {
      private:

      sf::Font font;
      sf::RenderWindow window;
      std::unique_ptr<GameState> currentState;

      public:

      Game ();

      const sf::Font& getFont () const { return font; }

      void run ();
      void changeState (std::unique_ptr<GameState> newState);
};

#endif // GAME_H