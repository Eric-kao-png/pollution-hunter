#include "./Character.hpp"

Character::Character(const std::string& name, int maxHealth, int attackPower, int speed, const Map& map)
    : name(name), maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed), 
      isAttacking(false), canTakeDamage(true), isTakingDamage(false),
      targetPoint(map.getPos()) {
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(map.getPos());
            shape.setSize(sf::Vector2f({50, 50}));
            shape.setOrigin(shape.getSize() / 2.f);
      }

bool Character::isMoving () const {
      if ((targetPoint.x - shape.getPosition().x) * (targetPoint.x - shape.getPosition().x) +
          (targetPoint.y - shape.getPosition().y) * (targetPoint.y - shape.getPosition().y) < speed * speed) {
            return false;
      }
      return true;
}

void Character::move () {
      sf::Vector2f direction({targetPoint.x - shape.getPosition().x, targetPoint.y - shape.getPosition().y});
      float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

      float adjustment = 0.01;
      shape.move(sf::Vector2f({direction.x / length * speed * adjustment, direction.y / length * speed * adjustment}));
}

void Character::setIsAttacking (bool isAttacking) {
      if (this -> isAttacking && isAttacking) {
            return;
      }

      this -> isAttacking = isAttacking;

      if (isAttacking) {
            attackClock = std::make_unique<sf::Clock>();
      } 
}

void Character::attack (const sf::Vector2f& mousePos) {
      attackShape = std::make_unique<sf::RectangleShape>();

      attackShape -> setFillColor(sf::Color::Blue);
      attackShape -> setSize(sf::Vector2f({70, 30}));
      attackShape -> setOrigin(sf::Vector2f({0, 15}));
      attackShape -> setPosition(shape.getPosition());

      double x = mousePos.x - shape.getPosition().x;
      double y = mousePos.y - shape.getPosition().y;
      double angleInRads = std::atan2(y, x);
      sf::Angle angle = sf::radians(angleInRads);
      attackShape -> setRotation(angle); 

      if (attackClock -> getElapsedTime().asSeconds() >= 1.5) {
            setIsAttacking(false);
            attackShape.reset();
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
      if (takeDamageClock) {
            if (takeDamageClock -> getElapsedTime().asSeconds() <= 2) {
                  return false;
            }
            takeDamageClock.reset();
      }
      return true;
}

bool Character::setIsTakingDamage (const Enemy& enemy) {
      if (enemy.getAttackShape() && enemy.getAttackShape() -> getGlobalBounds().findIntersection(shape.getGlobalBounds())) {
            return true;      
      }
      return false;
}

void Character::takeDamage (const Enemy& enemy) {
      currentHealth -= enemy.getAttackPower();
      takeDamageClock = std::make_unique<sf::Clock>();
}

void Character::update (const sf::Vector2f& mousePos, const std::vector<Enemy>& enemys) {
      if (isMoving()) {
            move();
      }
      if (isAttacking) {
            attack(mousePos);
      }
      canTakeDamage = setCanTakeDamage();
      for (auto& enemy : enemys) {
            isTakingDamage = setIsTakingDamage(enemy);
            if (canTakeDamage && isTakingDamage) {
                  takeDamage(enemy);
            }
      }
      
}

void Character::render (sf::RenderWindow& window) const {
      window.draw(shape);
      if (isAttacking && attackShape) {
            window.draw(*attackShape);
      }
}