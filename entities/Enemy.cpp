#include "./Enemy.hpp"

Enemy::Enemy (int maxHealth, int attackPower, int speed, const sf::Vector2f& startPos) 
      : maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed),
        canTakeDamage(true), isAlive(true), wantToAttack(false),
        targetPoint(startPos) {
            shape.setFillColor(sf::Color::Yellow);
            shape.setPosition(startPos);
            shape.setSize(sf::Vector2f({50, 50}));
            shape.setOrigin(shape.getSize() / 2.f);
      }

void Enemy::setTargetPoint (const Character& character) {
      targetPoint = character.getPos();
}

bool Enemy::isMoving () const{
      if ((targetPoint.x - shape.getPosition().x) * (targetPoint.x - shape.getPosition().x) +
          (targetPoint.y - shape.getPosition().y) * (targetPoint.y - shape.getPosition().y) < speed * speed) {
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

bool Enemy::setWantToAttack(const Character& character) {
      float distance = sqrt((shape.getPosition().x - character.getPos().x) * (shape.getPosition().x - character.getPos().x) + 
                            (shape.getPosition().x - character.getPos().x) * (shape.getPosition().x - character.getPos().x));
      if (distance <= 100) {
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

      attackShape -> setFillColor(sf::Color::Magenta);
      attackShape -> setSize(sf::Vector2f({40, 60}));
      attackShape -> setOrigin(sf::Vector2f({0, 20}));
      attackShape -> setPosition(shape.getPosition());

      double x = character.getPos().x - shape.getPosition().x;
      double y = character.getPos().y - shape.getPosition().y;
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

bool Enemy::isTakingDamage (const Character& character) const {
      if (character.getAttackShape()) {
            if (shape.getGlobalBounds().findIntersection(character.getAttackShape() -> getGlobalBounds())) {
                  return true;
            }
      }
      return false;
}

void Enemy::takeDamage (const Character& character) {
      currentHealth -= character.getAttackPower();
      canTakeDamage = false;
      takeDamageClock = std::make_unique<sf::Clock>();
}

void Enemy::update (const Character& character) {
      setTargetPoint(character);
      if (isMoving()) {
            move();
      }

      if (takeDamageClock) {
            if (takeDamageClock -> getElapsedTime().asSeconds() >= 1) {
                  canTakeDamage = true;
            }
      }

      if (isAlive) {
            if (currentHealth <= 0) {
                  setIsAlive(false);
            }
      }

      if (canTakeDamage && isTakingDamage(character)) {
            takeDamage(character);
      }

      wantToAttack = setWantToAttack(character);
      canAttack = setCanAttack();
      if (wantToAttack && canAttack) {
            attack(character);
      }
}

void Enemy::render (sf::RenderWindow& window) const {
      window.draw(shape);
      if(attackShape && wantToAttack && canAttack) {
            window.draw(*attackShape);
      }
}