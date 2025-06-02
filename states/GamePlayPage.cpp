#include "./GamePlayPage.hpp"

namespace{
      enum class SpawnEdge {up, right, down, left};
}

GamePlayPage::GamePlayPage(Game* game) 
      : game(game),
        quitButton({BUTTON_WIDTH / 2.f, WINDOW_HEIGHT - BUTTON_HEIGHT / 2.f}, {BUTTON_WIDTH, BUTTON_HEIGHT}, "Quit", game -> getFont()),
        score(0), scoreText(game -> getFont()),
        healthText(game -> getFont()), 
        difficultyText(game -> getFont()),
        gameover(false),
        map(), character("Hero", 5, 1, 1, map) {

            characterView.setCenter(character.getPosition());
            characterView.setSize(sf::Vector2f({128 * 4, 128 * 4}));
            characterView.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
            
            std::srand(static_cast<unsigned int>(std::time(nullptr)));

            scoreShape.setPosition(sf::Vector2f({GAMEPLAY_PAGE_WIDTH - SCORE_SHAPE_WIDTH / 2.f, GAMEPLAY_PAGE_HEIGHT - SCORE_SHAPE_HEIGHT / 2.f}));
            scoreShape.setSize(sf::Vector2f({SCORE_SHAPE_WIDTH, SCORE_SHAPE_HEIGHT}));
            scoreShape.setOrigin(scoreShape.getSize() / 2.f);
            scoreShape.setFillColor(sf::Color::White);

            scoreText.setPosition(scoreShape.getPosition() - sf::Vector2f({SCORE_SHAPE_WIDTH / 2.f - 20, scoreText.getGlobalBounds().size.y / 2.f}));
            scoreText.setCharacterSize(16);
            scoreText.setFillColor(sf::Color::Black);
            
            healthShape.setPosition(sf::Vector2f({GAMEPLAY_PAGE_WIDTH - HEALTH_SHAPE_WIDTH / 2.f, GAMEPLAY_PAGE_HEIGHT - HEALTH_SHAPE_HEIGHT / 2.f - SCORE_SHAPE_HEIGHT}));
            healthShape.setSize(sf::Vector2f({HEALTH_SHAPE_WIDTH, HEALTH_SHAPE_HEIGHT}));
            healthShape.setOrigin(healthShape.getSize() / 2.f);
            healthShape.setFillColor(sf::Color::White);

            healthText.setPosition(healthShape.getPosition() - sf::Vector2f({HEALTH_SHAPE_WIDTH / 2.f - 20, healthText.getGlobalBounds().size.y / 2.f}));
            healthText.setCharacterSize(16);
            healthText.setFillColor(sf::Color::Black);

            difficultyShape.setPosition(sf::Vector2f({GAMEPLAY_PAGE_WIDTH - DIFFICULTY_SHAPE_WIDTH / 2.f, GAMEPLAY_PAGE_HEIGHT - DIFFICULTY_SHAPE_HEIGHT / 2.f - SCORE_SHAPE_HEIGHT - HEALTH_SHAPE_HEIGHT}));
            difficultyShape.setSize(sf::Vector2f({DIFFICULTY_SHAPE_WIDTH, DIFFICULTY_SHAPE_HEIGHT}));
            difficultyShape.setOrigin(difficultyShape.getSize() / 2.f);
            difficultyShape.setFillColor(sf::Color::White);

            difficultyText.setPosition(difficultyShape.getPosition() - sf::Vector2f({DIFFICULTY_SHAPE_WIDTH / 2.f - 20, difficultyText.getGlobalBounds().size.y / 2.f}));
            difficultyText.setCharacterSize(16);
            difficultyText.setFillColor(sf::Color::Black);
            switch (game -> getdifficulty()) {
                  case Difficulty::easy:
                  difficultyText.setString("Difficulty:\neasy"); break;
                  case Difficulty::midium:
                  difficultyText.setString("Difficulty:\nmidium"); break;
                  case Difficulty::hard:
                  difficultyText.setString("Difficulty:\nhard"); break;
                  case Difficulty::very_hard:
                  difficultyText.setString("Difficulty:\nvery hard"); break;
                  default:
                  difficultyText.setString("Difficulty:\neasy");
            }
      }

void GamePlayPage::moveCharacterView () {
      characterView.setCenter(character.getPosition());
}

bool GamePlayPage::isSpawning () const {
      int chance = rand() % 70000;
      if (chance == 1) {
            return true;
      }
      return false;
}

sf::Vector2f GamePlayPage::getSpawningLocation (const Map& map) const {
      SpawnEdge spawnEdge = static_cast<SpawnEdge>(rand() % 4);
      switch (spawnEdge) {
            case SpawnEdge::up:
                  return map.getLeftUp() + sf::Vector2f({static_cast<float>(rand() % static_cast<int>(map.getSize().x)), 0}); break;
            case SpawnEdge::right:
                  return map.getLeftUp() + sf::Vector2f({0, static_cast<float>(rand() % static_cast<int>(map.getSize().y))}); break;
            case SpawnEdge::down:
                  return map.getLeftUp() + sf::Vector2f({static_cast<float>(rand() % static_cast<int>(map.getSize().x)), map.getSize().y}); break;
            case SpawnEdge::left:
                  return map.getLeftUp() + sf::Vector2f({map.getSize().x, static_cast<float>(rand() % static_cast<int>(map.getSize().y))}); break;
            default:
                  return map.getLeftUp();
      }
}

void GamePlayPage::enemySpawn (const Map& map) {
      if (game -> getdifficulty() == Difficulty::easy) {
            enemys.emplace_back(2, 1, 1, getSpawningLocation(map));
      } else if (game -> getdifficulty() == Difficulty::midium) {
            enemys.emplace_back(3, 1, 1, getSpawningLocation(map));
      } else if (game -> getdifficulty() == Difficulty::hard) {
            enemys.emplace_back(3, 2, 2, getSpawningLocation(map));
      } else {
            enemys.emplace_back(5, 2, 2, getSpawningLocation(map));
      }
      
}

void GamePlayPage::changeScoreText () {
      std::ostringstream oss;
      oss << "Score: " << score << std::endl;
      std::string scoreString(oss.str());
      scoreText.setString(scoreString);
}

void GamePlayPage::changeHealthText () {
      std::ostringstream oss;
      oss << "Health: " << character.getCurrentHealth() << std::endl;
      std::string healthString(oss.str());
      healthText.setString(healthString);
}

void GamePlayPage::handleInput (sf::RenderWindow &window) {
      while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>()) {
                  window.close();
            }

            if (const auto* mouseButtonPress = event -> getIf<sf::Event::MouseButtonPressed>()) {
                  setMousePos(window, window.getDefaultView());
                  if (quitButton.isClicked(mousePos)) {
                        
                        game -> changeState(std::make_unique<MainPage>(game));
                  }
                  setMousePos(window, characterView);
                  if (map.isClicked(mousePos)) {
                        
                        character.setTargetPoint(mousePos);
                  }
            }

            if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
                  setMousePos(window, characterView);
                  if (keyPressed -> code == sf::Keyboard::Key::A)  {
                        
                        character.setIsAttacking(true);
                  }
            }
      }
}

void GamePlayPage::update (sf::RenderWindow &window) {
      // map
      map.update();
      
      // character
      setMousePos(window, characterView);
      character.update(mousePos, enemys);
      moveCharacterView();
      changeHealthText();

      // enemys
      if (isSpawning()) {
            enemySpawn(map);
      }

      for (auto& enemy : enemys) {
            enemy.update(character);
      }

      for (auto it = enemys.begin(); it != enemys.end();) {
            if (!(it -> getIsAlive())) {
                  it = enemys.erase(it);
                  score += 100;
            } else {
                  ++it;
            }
      }
      changeScoreText();

      // gameover
      if (!character.getIsAlive()) {
            gameover = true;
      }
      if (gameover) {
            game -> changeState(std::make_unique<MainPage>(game));
      }
}

void GamePlayPage::render (sf::RenderWindow &window) {
      window.clear(sf::Color::Black);

      window.setView(characterView);
      map.render(window);
      character.render(window);
      for (auto& enemy : enemys) {
            enemy.render(window);
      }

      window.setView(window.getDefaultView());
      quitButton.render(window);
      window.draw(scoreShape);
      window.draw(scoreText);
      window.draw(healthShape);
      window.draw(healthText);
      window.draw(difficultyShape);
      window.draw(difficultyText);
      
      window.display();
}