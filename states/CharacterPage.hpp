#ifndef CHARACTERPAGE_H
#define CHARACTERPAGE_H

#include "../GameState.hpp"
#include "../Game.hpp"
#include "../entities/Button.hpp"
#include "./MainPage.hpp"

class Game;

class CharacterPage : public GameState {
      private:

      Game* game;

      Button quitButton;

      public:

      CharacterPage (Game* game);

      void handleInput(sf::RenderWindow &window) override;
      void update(sf::RenderWindow &window) override;
      void render(sf::RenderWindow &window) override;
      ~CharacterPage () override = default;
};

#endif // CHARACTERPAGE_H