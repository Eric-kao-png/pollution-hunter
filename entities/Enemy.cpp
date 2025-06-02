#include "./Enemy.hpp"

Enemy::Enemy (int maxHealth, int attackPower, int speed, const sf::Vector2f& startPos) 
      : maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed),
        isMoving(false), wantToAttack(false), canAttack(true), canTakeDamage(true), isTakingDamage(false), isAlive(true), 
        targetPoint(startPos),
        AnimatedSprite() {
      setPosition(startPos);
      setOrigin(getGlobalBounds().size / 2.f);
}

void Enemy::setTargetPoint (const Character& character) {
      targetPoint = character.getPosition();
}

Direction Enemy::determineDirection () const {
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
      

bool Enemy::setIsMoving () const {
      if (std::sqrt((targetPoint.x - getPosition().x) * (targetPoint.x - getPosition().x) +
                    (targetPoint.y - getPosition().y) * (targetPoint.y - getPosition().y)) <= 64) {
            return false;
      }
      return true;
}

void Enemy::run () {
      sf::Vector2f direction({targetPoint.x - getPosition().x, targetPoint.y - getPosition().y});
      float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

      float adjustment = 0.011;
      move(sf::Vector2f({direction.x / length * speed * adjustment, direction.y / length * speed * adjustment}));
}

bool Enemy::setWantToAttack(const Character& character) const {
      double distance = std::sqrt((getPosition().x - character.getPosition().x) * (getPosition().x - character.getPosition().x) + 
                            (getPosition().x - character.getPosition().x) * (getPosition().x - character.getPosition().x));
      if (distance <= 150) {
            return true;
      }
      return false;
}

bool Enemy::setCanAttack () {
      if (attackColdDown) {
            if (attackColdDown -> getElapsedTime().asSeconds() <= 5) {
                  return false;
            }
            attackColdDown.reset();
      }
      return true;
}

void Enemy::attack (const Character& character) {
      if (!attackClock) {
            attackClock = std::make_unique<sf::Clock>();
            attackShape = std::make_unique<sf::RectangleShape>();
      }

      attackShape -> setPosition(getPosition());
      attackShape -> setSize(sf::Vector2f({ENEMY_ATTACK_WIDTH, ENEMY_ATTACK_HEIGHT}));
      attackShape -> setOrigin(sf::Vector2f({0, ENEMY_ATTACK_HEIGHT / 2.f}));
      attackShape -> setFillColor(sf::Color::Magenta);

      double x = character.getPosition().x - getPosition().x;
      double y = character.getPosition().y - getPosition().y;
      double angleInRads = std::atan2(y, x);
      sf::Angle angle = sf::radians(angleInRads);
      attackShape -> setRotation(angle); 

      if (attackClock -> getElapsedTime().asSeconds() >= 2) {
            attackShape.reset();
            attackClock.reset();
            attackColdDown = std::make_unique<sf::Clock>();
      }
}

sf::RectangleShape* Enemy::getAttackShape () const {
      if (attackShape) {
            return attackShape.get();
      } else {
            return nullptr;
      }
}

bool Enemy::setCanTakeDamage () {
      if (takeDamageClock) {
            if (takeDamageClock -> getElapsedTime().asSeconds() <= 1) {
                  return false;
            }
            takeDamageClock.reset();
      }
      return true;
}

bool Enemy::setIsTakingDamage (const Character& character) const {
      if ((character.getAttackShape() != nullptr) && (character.getAttackShape() -> getGlobalBounds().findIntersection(getGlobalBounds()))) {
            return true;
      }
      return false;
}

void Enemy::takeDamage (const Character& character) {
      currentHealth -= character.getAttackPower();
      canTakeDamage = false;
      takeDamageClock = std::make_unique<sf::Clock>();
}

bool Enemy::setIsAlive () const {
      if (currentHealth > 0) {
            return true;
      }
      return false;
}

void Enemy::update (const Character& character, float deltaTime) {
      // move
      setTargetPoint(character);
      direction = determineDirection();
      isMoving = setIsMoving();
      if (isMoving) {
            run();
      }

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
      
      // attack
      wantToAttack = setWantToAttack(character);
      canAttack = setCanAttack();
      if (wantToAttack && canAttack) {
            // play("attack");
            attack(character);
      }

      // take damage
      canTakeDamage = setCanTakeDamage();
      isTakingDamage = setIsTakingDamage(character);
      if (canTakeDamage && isTakingDamage) {
            takeDamage(character);
      }

      AnimatedSprite::update(deltaTime);

      // live
      isAlive = setIsAlive();
}

void Enemy::render (sf::RenderWindow& window) const {
      if (attackShape) {
            window.draw(*attackShape);
      }
}