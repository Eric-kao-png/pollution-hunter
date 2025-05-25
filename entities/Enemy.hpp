#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "./Map.hpp"
#include "./Character.hpp"

class Enemy {
      private:

      int maxHealth;
      int currentHealth;
      int attackPower;
      int speed;

      sf::RectangleShape shape;
      sf::Vector2f targetPoint;

      public:

      Enemy (int maxHealth, int attackPower, int speed, const sf::Vector2f& startPos);

      void randomSpawn (const Map& map);
      void takeDamage (const Character& character);
      

      void update ();
      void render (sf::RenderWindow& window) const;
};

#endif // ENEMY_H