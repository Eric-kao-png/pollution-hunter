#include "./Enemy.hpp"

Enemy::Enemy (int maxHealth, int attackPower, int speed, const sf::Vector2f& startPos) 
      : maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed),
        isMoving(false), wantToAttack(false), canAttack(true), canTakeDamage(true), isTakingDamage(false), isAlive(true), 
        targetPoint(startPos) {
      shape.setPosition(startPos);
      shape.setSize(sf::Vector2f({ENEMY_SIZE, ENEMY_SIZE}));
      shape.setOrigin(shape.getSize() / 2.f);
      shape.setFillColor(sf::Color::Yellow);
}

void Enemy::setTargetPoint (const Character& character) {
      targetPoint = character.getPosition();
}

bool Enemy::setIsMoving () const {
      if (std::sqrt((targetPoint.x - shape.getPosition().x) * (targetPoint.x - shape.getPosition().x) +
                    (targetPoint.y - shape.getPosition().y) * (targetPoint.y - shape.getPosition().y)) <= 64) {
            return false;
      }
      return true;
}

void Enemy::move () {
      sf::Vector2f direction({targetPoint.x - shape.getPosition().x, targetPoint.y - shape.getPosition().y});
      float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

      float adjustment = 0.011;
      shape.move(sf::Vector2f({direction.x / length * speed * adjustment, direction.y / length * speed * adjustment}));
}

bool Enemy::setWantToAttack(const Character& character) const {
      double distance = std::sqrt((shape.getPosition().x - character.getPosition().x) * (shape.getPosition().x - character.getPosition().x) + 
                            (shape.getPosition().x - character.getPosition().x) * (shape.getPosition().x - character.getPosition().x));
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

      attackShape -> setPosition(shape.getPosition());
      attackShape -> setSize(sf::Vector2f({ENEMY_ATTACK_WIDTH, ENEMY_ATTACK_HEIGHT}));
      attackShape -> setOrigin(sf::Vector2f({0, ENEMY_ATTACK_HEIGHT / 2.f}));
      attackShape -> setFillColor(sf::Color::Magenta);

      double x = character.getPosition().x - shape.getPosition().x;
      double y = character.getPosition().y - shape.getPosition().y;
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
      if ((character.getAttackShape() != nullptr) && (character.getAttackShape() -> getGlobalBounds().findIntersection(shape.getGlobalBounds()))) {
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

void Enemy::update (const Character& character) {
      // move
      setTargetPoint(character);
      isMoving = setIsMoving();
      if (isMoving) {
            move();
      }

      // attack
      wantToAttack = setWantToAttack(character);
      canAttack = setCanAttack();
      if (wantToAttack && canAttack) {
            attack(character);
      }

      // take damage
      canTakeDamage = setCanTakeDamage();
      isTakingDamage = setIsTakingDamage(character);
      if (canTakeDamage && isTakingDamage) {
            takeDamage(character);
      }

      // live
      isAlive = setIsAlive();
}

void Enemy::render (sf::RenderWindow& window) const {
      window.draw(shape);
      if (attackShape) {
            window.draw(*attackShape);
      }
}