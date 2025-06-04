#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "./Map.hpp"
#include "./Enemy.hpp"
#include "./AnimatedSprite.hpp"

constexpr int CHARACTER_SIZE = 64;
constexpr int CHARACTER_ATTACK_WIDTH = 96;
constexpr int CHARACTER_ATTACK_HEIGHT = 32;

class Enemy;

class Character : public AnimatedSprite {
      private:

      // basic attributes
      std::string name;
      int maxHealth;
      int currentHealth;
      int attackPower;
      int speed;
      
      // about moving
      bool isMoving;
      sf::Vector2f targetPoint;
      Direction direction;

      Direction determineDirection () const;

      // about attacking
      bool isAttacking;
      bool canAttack;
      std::unique_ptr<sf::RectangleShape> attackShape;
      std::unique_ptr<sf::Clock> attackClock;
      std::unique_ptr<sf::Clock> attackColdDown;
      sf::Texture bulletTexture;

      // about taking damage
      bool canTakeDamage;
      bool isTakingDamage;
      std::unique_ptr<sf::Clock> takeDamageColdDown;

      // about life
      bool isAlive;

      public:

      Character (const std::string& name, int maxHealth, int attackPower, int speed, const Map& map);

      // function about basic attributes
      std::string getName () const { return name; }
      int getMaxHealth () const { return maxHealth; }
      int getCurrentHealth () const { return currentHealth; }
      int getAttackPower () const { return attackPower; }
      int getSpeed () const { return speed; }
      sf::Vector2f getPosition () const { return AnimatedSprite::getPosition(); }

      // function about moving
      void setTargetPoint (const sf::Vector2f& point) { targetPoint = point; }
      bool setIsMoving () const;
      void run ();

      // function about attacking
      void setIsAttacking (bool isAttacking); 
      bool getIsAttacking () { return isAttacking; }
      bool setCanAttack ();
      void attack (const sf::Vector2f& mousePos);
      sf::RectangleShape* getAttackShape () const ;

      // function about taking damage
      bool setCanTakeDamage ();
      bool setIsTakingDamage (const Enemy& enemy) const;
      void takeDamage (const Enemy& enemy);

      // function about life
      bool setIsAlive () const;
      bool getIsAlive () const { return isAlive; }

      void update (const sf::Vector2f& mousePos, const std::vector<Enemy>& enemys, float deltaTime);
      void render (sf::RenderWindow& window) const;
};

#endif // CHARACTER_H