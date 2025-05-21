#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class GameState {
      public:

      virtual void handleInput (sf::RenderWindow &window) = 0;
      virtual void update (sf::RenderWindow &window) = 0;
      virtual void render (sf::RenderWindow &window) = 0;
      virtual ~GameState () = default;
};

#endif // GAMESTATE_H