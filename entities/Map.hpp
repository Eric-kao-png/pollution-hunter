#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map {
      private:

      sf::RectangleShape shape;

      public:

      Map ();

      bool isClicked (const sf::Vector2f mousePos) const;

      sf::Vector2f getPosition () const { return shape.getPosition(); } 
      sf::Vector2f getSize () const { return shape.getSize(); }

      void update ();
      void render (sf::RenderWindow& window) const;
};

#endif // MAP_H