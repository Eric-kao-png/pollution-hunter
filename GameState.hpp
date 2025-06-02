#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState {
      protected:

      sf::Vector2f mousePos;
      const sf::Vector2f& setMousePos (const sf::RenderWindow& window, const sf::View& currentView);

      public:

      virtual void handleInput (sf::RenderWindow &window) = 0;
      virtual void update (sf::RenderWindow &window, float deltaTime) = 0;
      virtual void render (sf::RenderWindow &window) = 0;
      virtual ~GameState () = default;
};

#endif // GAMESTATE_H