#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "./Map.hpp"

class Character {
      private:

      std::string name;
      int maxHealth;
      int currentHealth;
      int attackPower;
      int speed;

      // sf::Texture texture;
      // sf::Sprite sprite;

      sf::RectangleShape shape;
      sf::Vector2f targetPoint;
      bool isAttacking;
      std::unique_ptr<sf::RectangleShape> attackShape;
      std::unique_ptr<sf::Clock> attackClock;

      public:

      Character (const std::string& name, int maxHealth, int attackPower, int speed, const Map& map);

      std::string getName () const { return name; }
      int getMaxHealth () const { return maxHealth; }
      int getCurrentHealth () { return currentHealth; }
      int getAttackPower () const { return attackPower; }
      int getSpeed () const { return speed; }
      sf::Vector2f getPos () const { return shape.getPosition(); }

      void setTargetPoint (const sf::Vector2f point) { targetPoint = point; }

      bool isMoving () const;
      void move ();

      void setIsAttacking (bool isAttacking); 
      bool getIsAttacking () { return isAttacking; }
      void attack (const sf::Vector2f& mousePos);

      void update (const sf::Vector2f& mousePos);
      void render (sf::RenderWindow& window) const;
};

#endif // CHARACTER_H