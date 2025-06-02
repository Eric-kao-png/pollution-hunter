#ifndef CHARACTERPAGE_HPP
#define CHARACTERPAGE_HPP

#include "../GameState.hpp"
#include "../Game.hpp"
#include "../entities/Button.hpp"
#include "../entities/Character.hpp"
#include "./MainPage.hpp"

constexpr int CHARACTER_PAGE_WIDTH = 128 * 6;
constexpr int CHARACTER_PAGE_HEIGHT = 128 * 6;

class Game;

class CharacterPage : public GameState {
      private:

      Game* game;

      // buttons
      Button quitButton;
      
      public:

      CharacterPage (Game* game);

      void handleInput(sf::RenderWindow &window) override;
      void update(sf::RenderWindow &window, float deltaTime) override;
      void render(sf::RenderWindow &window) override;
      ~CharacterPage () override = default;
};

#endif // CHARACTERPAGE_HPP