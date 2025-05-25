#ifndef GAMEPLAYPAGE_H
#define GAMEPLAYPAGE_H

#include "../GameState.hpp"
#include "../Game.hpp"
#include "../entities/Button.hpp"
#include "../entities/Character.hpp"
#include "../entities/Map.hpp"

class Game;

class GamePlayPage : public GameState {
      private:

      Game* game;

      Button quitButton;
      Map map;
      Character character;

      sf::Vector2f mousePos;

      public:

      GamePlayPage (Game* game);

      void handleInput(sf::RenderWindow &window) override;
      void update(sf::RenderWindow &window) override;
      void render(sf::RenderWindow &window) override;
      ~GamePlayPage () override = default;
};

#endif // GAMEPLAYPAGE_H