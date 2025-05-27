#include "Map.hpp"

// Map::Map (const sf::Texture& texture) : texture(texture), sprite(this -> texture) {}

Map::Map () {
      shape.setPosition(sf::Vector2f({400, 300}));
      shape.setSize(sf::Vector2f({600, 400}));
      shape.setOrigin(shape.getSize() / 2.f);
      shape.setFillColor(sf::Color::Green);
}

bool Map::isClicked (const sf::Vector2f mousePos) const {
      return shape.getGlobalBounds().contains(mousePos);
}

void Map::update () {

}

void Map::render (sf::RenderWindow& window) const {
      window.draw(shape);
}