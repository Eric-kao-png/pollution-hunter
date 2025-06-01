#include "./GameState.hpp"

const sf::Vector2f& GameState::setMousePos (const sf::RenderWindow& window, const sf::View& currentView) {
      sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
      mousePos = window.mapPixelToCoords(mousePosPixel, currentView);
      return mousePos;
}