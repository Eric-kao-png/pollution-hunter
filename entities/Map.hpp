#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map {
      private:

      // sf::Texture texture;
      // sf::Sprite sprite;
      sf::RectangleShape shape;

      public:

      // Map (const sf::Texture& texture);
      Map ();

      bool isClicked (const sf::Vector2f mousePos) const;
      sf::Vector2f getPos () const { return shape.getPosition(); } 
      sf::Vector2f getOrigin () const { return shape.getOrigin(); }
      sf::Vector2f getSize () const { return shape.getSize(); }

      void update ();
      void render (sf::RenderWindow& window) const;
};

#endif // MAP_H