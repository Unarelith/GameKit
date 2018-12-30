/*
 * =====================================================================================
 *
 *       Filename:  Sprite.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:48:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_SPRITE_HPP_
#define GK_SPRITE_HPP_

#include "gk/gui/Image.hpp"
#include "gk/gui/SpriteAnimation.hpp"

namespace gk {

class Sprite : public Image {
	public:
		Sprite() = default;
		Sprite(const std::string &textureName, u16 frameWidth, u16 frameHeight, bool isAnimated = false);

		void load(const Sprite &sprite);
		void load(const std::string &textureName, u16 frameWidth, u16 frameHeight, bool isAnimated = false);

		void updateAnimations();

		void addAnimation(const SpriteAnimation &animation) { m_animations.emplace_back(animation); }

		u16 currentFrame() const { return m_currentFrame; }

		u16 frameWidth() const { return m_frameWidth; }
		u16 frameHeight() const { return m_frameHeight; }

		bool hasAnimations() { return m_animations.size() != 0; }

		SpriteAnimation &currentAnimation() { return m_animations.at(m_currentAnimation); }
		const SpriteAnimation &currentAnimation() const { return m_animations.at(m_currentAnimation); }

		void setCurrentFrame(u16 currentFrame);
		void setCurrentAnimation(u16 currentAnimation);

		bool isAnimated() const { return m_isAnimated; }
		void setAnimated(bool isAnimated) { m_isAnimated = isAnimated; }

	private:
		std::vector<SpriteAnimation> m_animations;

		u16 m_currentFrame = 0;
		u16 m_currentAnimation = 0;
		u16 m_previousAnimation = 0;

		u16 m_frameWidth = 0;
		u16 m_frameHeight = 0;

		bool m_isAnimated = false;
};

} // namespace gk

#endif // GK_SPRITE_HPP_
