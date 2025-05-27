#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "./Map.hpp"
#include "./Character.hpp"

class Character;

class Enemy {
      private:

      int maxHealth;
      int currentHealth;
      int attackPower;
      int speed;
      sf::RectangleShape shape;

      sf::Vector2f targetPoint;

      bool wantToAttack;
      bool canAttack;
      std::unique_ptr<sf::Clock> attackClock;
      std::unique_ptr<sf::Clock> attackColdDown;
      std::unique_ptr<sf::RectangleShape> attackShape;

      bool canTakeDamage;
      std::unique_ptr<sf::Clock> takeDamageClock;

      bool isAlive;

      public:

      Enemy (int maxHealth, int attackPower, int speed, const sf::Vector2f& startPos);

      int getAttackPower () const { return attackPower; }

      void setTargetPoint (const Character& character);
      bool isMoving () const;
      void move ();

      bool setWantToAttack (const Character& character);
      bool setCanAttack ();
      void attack (const Character& character);
      sf::RectangleShape* getAttackShape () const;

      bool isTakingDamage (const Character& character) const;
      void takeDamage (const Character& character);

      void setIsAlive (bool isAlive) { this -> isAlive = isAlive; }
      bool getIsAlive () const { return isAlive; }

      void update (const Character& character);
      void render (sf::RenderWindow& window) const;
};

#endif // ENEMY_H