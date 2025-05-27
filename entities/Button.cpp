#include "Button.hpp"

Button::Button (const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font) 
      : label(font) {

      shape.setPosition(position);
      shape.setSize(size);
      shape.setFillColor(sf::Color::White);

      label.setString(text);
      label.setCharacterSize(16);
      label.setFillColor(sf::Color::Black);
      label.setPosition({
            position.x + (size.x - label.getGlobalBounds().size.x) / 2.f, 
            position.y + (size.y - label.getGlobalBounds().size.y) / 2.f});
}

bool Button::isClicked (const sf::Vector2f& mousePos) const {
      return shape.getGlobalBounds().contains(mousePos);
}

void Button::render (sf::RenderWindow& window) const {
      window.draw(shape);
      window.draw(label);
}