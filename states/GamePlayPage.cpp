#include "./GamePlayPage.hpp"

GamePlayPage::GamePlayPage(Game* game) 
      : game(game),
        quitButton({50, 50}, {100, 50}, "Quit", game -> getFont()),
        score(0), scoreText(game -> getFont()),
        healthText(game -> getFont()), 
        gameover(false),
        character("Hero", 5, 1, 1, map) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));

            scoreShape.setPosition(sf::Vector2f({200, 500}));
            scoreShape.setSize(sf::Vector2f({100, 50}));
            scoreShape.setFillColor(sf::Color::White);

            scoreText.setPosition(scoreShape.getPosition());
            scoreText.setCharacterSize(16);
            scoreText.setFillColor(sf::Color::Black);
            
            healthShape.setPosition(sf::Vector2f({300, 500}));
            healthShape.setSize(sf::Vector2f({100, 50}));
            healthShape.setFillColor(sf::Color::White);

            healthText.setPosition(healthShape.getPosition());
            healthText.setCharacterSize(16);
            healthText.setFillColor(sf::Color::Black);
      }

bool GamePlayPage::isSpawning () const {
      int chance = rand() % 70000;
      if (chance == 1) {
            return true;
      }
      return false;
}

void GamePlayPage::enemySpawn (const Map& map) {
      enemys.emplace_back(2, 1, 1, map.getPosition() - map.getSize() / 2.f);
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

            setMousePos(window);

            if (const auto* mouseButtonPress = event -> getIf<sf::Event::MouseButtonPressed>()) {

                  if (quitButton.isClicked(mousePos)) {
                        game -> changeState(std::make_unique<MainPage>(game));
                  }

                  if (map.isClicked(mousePos)) {
                        character.setTargetPoint(mousePos);
                  }
            }

            if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
                  
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
      character.update(mousePos, enemys);
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

      quitButton.render(window);
      window.draw(scoreShape);
      window.draw(scoreText);
      window.draw(healthShape);
      window.draw(healthText);
      map.render(window);
      character.render(window);
      for (auto& enemy : enemys) {
            enemy.render(window);
      }
      
      window.display();
}