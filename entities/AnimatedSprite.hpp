#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "./Animation.hpp"

class Animation;

enum class Direction {front, right, back, left};

class AnimatedSprite : public sf::Sprite {
      protected:

      sf::Texture initTexture;
      std::unordered_map<std::string, Animation> animations;
      std::unordered_map<std::string, sf::Texture> textures;
      std::string currentAnimation;

      public:

      AnimatedSprite ();

      void addAnimation (const std::string& animationName, const std::string& texturePath, Animation animation);
      void play (const std::string& AnimationName);
      void update (float deltaTime);
};

#endif // ANIMATED_SPRITE_HPP