#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "./Map.hpp"
#include "./Character.hpp"
#include "./AnimatedSprite.hpp"
#include <iostream>

constexpr int ENEMY_SIZE = 64;
constexpr int ENEMY_ATTACK_WIDTH = 48;
constexpr int ENEMY_ATTACK_HEIGHT = 64;

class Character;

class Enemy : public AnimatedSprite {
      private:

      // basic attributes
      int maxHealth;
      int currentHealth;
      int attackPower;
      int speed;

      // about moving
      bool isMoving;
      sf::Vector2f targetPoint;
      Direction direction;

      Direction determineDirection () const;

      void setTargetPoint (const Character& character);
      bool setIsMoving () const;
      void run ();

      // about attacking
      bool wantToAttack;
      bool canAttack;
      std::unique_ptr<sf::Clock> attackClock;
      std::unique_ptr<sf::Clock> attackColdDown;
      std::unique_ptr<sf::RectangleShape> attackShape;

      bool setWantToAttack (const Character& character) const;
      bool setCanAttack ();
      void attack (const Character& character);

      // about taking damage
      bool canTakeDamage;
      bool isTakingDamage;
      std::unique_ptr<sf::Clock> takeDamageClock;

      bool setCanTakeDamage ();
      bool setIsTakingDamage (const Character& character) const;
      void takeDamage (const Character& character);

      // about life
      bool isAlive;

      public:

      Enemy (int maxHealth, int attackPower, int speed, const sf::Vector2f& startPos);

      bool setIsAlive () const;

      int getAttackPower () const { return attackPower; }
      sf::RectangleShape* getAttackShape () const;
      bool getIsAlive () const { return isAlive; }

      void update (const Character& character, float deltaTime);
      void render (sf::RenderWindow& window) const;
};

#endif // ENEMY_H