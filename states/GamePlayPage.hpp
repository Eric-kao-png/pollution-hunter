#ifndef GAMEPLAYPAGE_H
#define GAMEPLAYPAGE_H

#include <sstream>
#include "../GameState.hpp"
#include "../Game.hpp"
#include "../entities/Button.hpp"
#include "../entities/Character.hpp"
#include "../entities/Map.hpp"
#include "../entities/Enemy.hpp"

constexpr int GAMEPLAY_PAGE_WIDTH = 128 * 6;
constexpr int GAMEPLAY_PAGE_HEIGHT = 128 * 6;
constexpr int BUTTON_WIDTH = 100;
constexpr int BUTTON_HEIGHT = 50;
constexpr int SCORE_SHAPE_WIDTH = 100;
constexpr int SCORE_SHAPE_HEIGHT = 50;
constexpr int HEALTH_SHAPE_WIDTH = 100;
constexpr int HEALTH_SHAPE_HEIGHT = 50;

class Game;

class GamePlayPage : public GameState {
      private:

      Game* game;

      // view
      sf::View characterView;
      void moveCharacterView ();

      // buttons
      Button quitButton;

      // score
      sf::RectangleShape scoreShape;
      int score;
      sf::Text scoreText;
      void changeScoreText ();

      // current health
      sf::RectangleShape healthShape;
      sf::Text healthText;
      void changeHealthText ();

      // game objects
      Map map;
      Character character;
      std::vector<Enemy> enemys;
      bool isSpawning () const;
      void enemySpawn (const Map& map);
      sf::Vector2f getSpawningLocation (const Map& map) const;

      // gameover
      bool gameover;

      public:

      GamePlayPage (Game* game);

      void handleInput(sf::RenderWindow &window) override;
      void update(sf::RenderWindow &window) override;
      void render(sf::RenderWindow &window) override;
      ~GamePlayPage () override = default;
};

#endif // GAMEPLAYPAGE_H