#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include "./AnimatedSprite.hpp"

class AnimatedSprite;

class Animation {
      private:

      int startX;
      int startY;
      int frameWidth;
      int frameHeight;
      int frameCount; 
      float durationPerFrame;

      int currentFrame;
      float elapsedTime;

      public:

      Animation () = default;
      Animation (int x, int y, int width, int height, int count, float duration);

      void update (float deltaTime);
      void reset ();
      sf::IntRect getCurrentFrameRect () const;
};

#endif // ANIMATION_HPP