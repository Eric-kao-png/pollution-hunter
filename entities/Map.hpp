#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

constexpr int MAP_SIZE = 128 * 12;

class Map {
      private:

      sf::Texture mapTexture;
      sf::Sprite mapSprite;

      public:

      Map ();

      bool isClicked (const sf::Vector2f mousePos) const;

      sf::Vector2f getPosition () const { return mapSprite.getPosition(); } 
      sf::Vector2f getSize () const { return mapSprite.getGlobalBounds().size; }
      sf::Vector2f getLeftUp () const { return mapSprite.getPosition() - mapSprite.getGlobalBounds().size / 2.f; }

      void update ();
      void render (sf::RenderWindow& window) const;
};

#endif // MAP_H