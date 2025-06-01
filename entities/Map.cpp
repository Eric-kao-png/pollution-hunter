#include "Map.hpp"

// Map::Map (const sf::Texture& texture) : texture(texture), sprite(this -> texture) {}

Map::Map () : mapTexture("./assets/map.png"), mapSprite(mapTexture) {
      mapSprite.setPosition(sf::Vector2f({0, 0}));
      // shape.setSize(sf::Vector2f({MAP_SIZE, MAP_SIZE}));
      mapSprite.setOrigin(mapSprite.getGlobalBounds().size / 2.f);
      // shape.setFillColor(sf::Color::Green);
}

bool Map::isClicked (const sf::Vector2f mousePos) const {
      return mapSprite.getGlobalBounds().contains(mousePos);
}

void Map::update () {

}

void Map::render (sf::RenderWindow& window) const {
      window.draw(mapSprite);
}