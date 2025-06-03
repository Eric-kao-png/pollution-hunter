#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite () : initTexture("./assets/empty.png"), sf::Sprite(initTexture, sf::IntRect({0, 0}, {64, 64})) {}

void AnimatedSprite::addAnimation (const std::string& animationName, const std::string& texturePath, Animation animation) {
      animations[animationName] = animation;
      textures[animationName] = sf::Texture(texturePath);
}

void AnimatedSprite::play (const std::string& animationName) {
      if (!animations.count(animationName)) {
            return;
      }
      if (animationName == currentAnimation) {
            return;
      }
      currentAnimation = animationName;
      setTexture(textures.at(animationName));
      setOrigin(getGlobalBounds().size / 2.f);
      animations.at(animationName).reset();
}

void AnimatedSprite::update (float deltaTime) {
      if (!animations.count(currentAnimation)) {
            return;
      }
      
      Animation& animation = animations.at(currentAnimation);
      animation.update(deltaTime);
      setTextureRect(animation.getCurrentFrameRect());
}