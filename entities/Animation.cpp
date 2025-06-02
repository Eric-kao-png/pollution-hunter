#include "Animation.hpp"

Animation::Animation (int x, int y, int width, int height, int count, float duration) : 
startX(x), startY(y), frameWidth(width), frameHeight(height), frameCount(count), durationPerFrame(duration),
currentFrame(0), elapsedTime(0.f) {}

void Animation::update (float deltaTime) {
      elapsedTime += deltaTime;

      if (elapsedTime >= durationPerFrame) {
            elapsedTime = 0;
            currentFrame = (currentFrame + 1) % frameCount;
      }
}

void Animation::reset () {
      currentFrame = 0;
      elapsedTime = 0;
}

sf::IntRect Animation::getCurrentFrameRect () const {
      return sf::IntRect({startX + currentFrame * frameWidth, startY}, {frameWidth, frameHeight});
}