#include "./Character.hpp"

Character::Character(const std::string& name, int maxHealth, int attackPower, int speed, const Map& map)
    : name(name), maxHealth(maxHealth), currentHealth(maxHealth), attackPower(attackPower), speed(speed), 
      targetPoint(map.getPos()),
      shape(sf::Vector2f({50, 50})) {
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

      float adjustment = 0.05;
      shape.move(sf::Vector2f({direction.x / length * speed * adjustment, direction.y / length * speed * adjustment}));
}

void Character::update () {
      if (isMoving()) {
            move();
      }
}

void Character::render (sf::RenderWindow& window) const {
      window.draw(shape);
}