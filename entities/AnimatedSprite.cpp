#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite () : initTexture("./assets/m-front1.png"), sf::Sprite(initTexture) {
      addAnimation("frontRun", "./assets/m-front.png", Animation(0, 0, 64, 64, 3, 0.2));
      addAnimation("rightRun", "./assets/m-right.png", Animation(0, 0, 64, 64, 2, 0.2));
      addAnimation("backRun", "./assets/m-back.png", Animation(0, 0, 64, 64, 3, 0.2));
      addAnimation("leftRun", "./assets/m-left.png", Animation(0, 0, 64, 64, 2, 0.2));
}

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