#include "./Character.hpp"

Character::Character(const std::string& name, int maxHealth, int attackPower, int speed, const Map& map)
    : name(name), maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed), 
      isMoving(false), isAttacking(false), canAttack(true), canTakeDamage(true), isTakingDamage(false), isAlive(true),
      targetPoint(map.getPosition()) {
            setPosition(map.getPosition());
            setOrigin(getGlobalBounds().size / 2.f);

            addAnimation("frontRun", "./assets/s-front.png", Animation(0, 0, 64, 64, 3, 0.2));
            addAnimation("rightRun", "./assets/s-right.png", Animation(0, 0, 64, 64, 3, 0.2));
            addAnimation("backRun", "./assets/s-back.png", Animation(0, 0, 64, 64, 3, 0.2));
            addAnimation("leftRun", "./assets/s-left.png", Animation(0, 0, 64, 64, 3, 0.2));
            addAnimation("idle", "./assets/s-idle.png", Animation(0, 0, 64, 64, 1, 0.2));
      }

bool Character::setIsMoving () const {
      if ((targetPoint.x - getPosition().x) * (targetPoint.x - getPosition().x) +
          (targetPoint.y - getPosition().y) * (targetPoint.y - getPosition().y) < speed * speed) {
            return false;
      }
      return true;
}

Direction Character::determineDirection () const {
      double deltaX = targetPoint.x - getPosition().x;
      double deltaY = targetPoint.y - getPosition().y;
      double angleInRads = std::atan2(deltaY, deltaX);

      if (-3 * M_PI / 4 <= angleInRads && angleInRads < -1 * M_PI / 4) {
            return Direction::back;
      } else if (-1 * M_PI / 4 <= angleInRads && angleInRads < M_PI / 4) {
            return Direction::right;
      } else if (M_PI / 4 <= angleInRads && angleInRads < 3 * M_PI / 4) {
            return Direction::front;
      } else {
            return Direction::left;
      }
}

void Character::run () {
      sf::Vector2f direction({targetPoint.x - getPosition().x, targetPoint.y - getPosition().y});
      float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
      if (length == 0) {
            return;
      }

      float adjustment = 0.01;
      move(sf::Vector2f({direction.x / length * speed * adjustment, direction.y / length * speed * adjustment}));
}

void Character::setIsAttacking (bool isAttacking) {
      if (!canAttack) {
            return;
      }
      this -> isAttacking = isAttacking;
}

bool Character::setCanAttack () {
      if (attackColdDown) {
            if (attackColdDown -> getElapsedTime().asSeconds() <= 0.5) {
                  return false;
            }
            attackColdDown.reset();
      }
      return true;
}

void Character::attack (const sf::Vector2f& mousePos) {
      if (!attackClock) {
            attackClock = std::make_unique<sf::Clock>();
            attackShape = std::make_unique<sf::RectangleShape>();
      }

      attackShape -> setPosition(getPosition());
      attackShape -> setSize(sf::Vector2f({CHARACTER_ATTACK_WIDTH, CHARACTER_ATTACK_HEIGHT}));
      attackShape -> setOrigin(sf::Vector2f({0, CHARACTER_ATTACK_HEIGHT / 2.f}));
      attackShape -> setFillColor(sf::Color::Blue);

      double x = mousePos.x - getPosition().x;
      double y = mousePos.y - getPosition().y;
      double angleInRads = std::atan2(y, x);
      sf::Angle angle = sf::radians(angleInRads);
      attackShape -> setRotation(angle); 

      if (attackClock -> getElapsedTime().asSeconds() >= 1.5) {
            attackClock.reset();
            attackShape.reset();
            attackColdDown = std::make_unique<sf::Clock>();
            isAttacking = false;
      }
}

sf::RectangleShape* Character::getAttackShape () const {
      if (attackShape) {
            return attackShape.get();
      } else {
            return nullptr;
      }
}

bool Character::setCanTakeDamage () {
      if (takeDamageColdDown) {
            if (takeDamageColdDown -> getElapsedTime().asSeconds() <= 2) {
                  return false;
            }
            takeDamageColdDown.reset();
      }
      return true;
}

bool Character::setIsTakingDamage (const Enemy& enemy) const {
      if ((enemy.getAttackShape() != nullptr) && (enemy.getAttackShape() -> getGlobalBounds().findIntersection(getGlobalBounds()))) {
            return true;      
      }
      return false;
}

void Character::takeDamage (const Enemy& enemy) {
      currentHealth -= enemy.getAttackPower();
      takeDamageColdDown = std::make_unique<sf::Clock>();
}

bool Character::setIsAlive () const {
      if (currentHealth > 0) {
            return true;
      }
      return false;
}

void Character::update (const sf::Vector2f& mousePos, const std::vector<Enemy>& enemys, float deltaTime) {
      // move
      isMoving = setIsMoving();
      direction = determineDirection();
      if (isMoving) {
            switch (direction) {
                  case Direction::front:
                        play("frontRun"); break;
                  case Direction::right:
                        play("rightRun"); break;
                  case Direction::back:
                        play("backRun"); break;
                  case Direction::left:
                        play("leftRun"); break;
            }
            run();
      } else {
            play("idle");
      }

      // attack
      canAttack = setCanAttack();
      if (isAttacking && canAttack) {
            attack(mousePos);
      }

      // take damege
      canTakeDamage = setCanTakeDamage();
      for (auto& enemy : enemys) {
            isTakingDamage = setIsTakingDamage(enemy);
            if (canTakeDamage && isTakingDamage) {
                  takeDamage(enemy);
                  break;
            }
      }

      AnimatedSprite::update(deltaTime);

      // life
      isAlive = setIsAlive();
}

void Character::render (sf::RenderWindow& window) const {
      if (attackShape) {
            window.draw(*attackShape);
      }
}