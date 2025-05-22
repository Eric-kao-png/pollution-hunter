#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
      private:

      sf::RectangleShape shape;
      sf::Text label;

      public:

      Button (const sf::Vector2f& position,
              const sf::Vector2f& size,
              const std::string& text,
              const sf::Font& font);

      bool isClicked (const sf::Vector2f mousePos) const;
      void render (sf::RenderWindow& window) const;
};

#endif // BUTTON_H