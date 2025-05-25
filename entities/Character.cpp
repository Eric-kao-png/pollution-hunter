#include "./Character.hpp"

Character::Character(const std::string& name, int maxHealth, int attackPower, int speed, const Map& map)
    : name(name), maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed), 
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

void Character::attack (const sf::Vector2f& mousePos) {
      attackShape = std::make_unique<sf::RectangleShape>();

      attackShape -> setFillColor(sf::Color::Blue);
      attackShape -> setSize(sf::Vector2f({50, 30}));
      attackShape -> setOrigin(sf::Vector2f({0, 15}));
      attackShape -> setPosition(shape.getPosition());

      double x = mousePos.x - shape.getPosition().x;
      double y = mousePos.y - shape.getPosition().y;
      double angleInRads = std::atan2(y, x);
      sf::Angle angle = sf::radians(angleInRads);
      attackShape -> setRotation(angle); 
}

void Character::update (const sf::Vector2f& mousePos) {
      if (isMoving()) {
            move();
      }
      if (isAttacking) {
            attack(mousePos);
      }
}

void Character::render (sf::RenderWindow& window) const {
      window.draw(shape);
      if (isAttacking && attackShape) {
            window.draw(*attackShape);
      }
}