/*
 * =====================================================================================
 *
 *       Filename:  Transformable.hpp
 *
 *    Description:
 *
 *        Created:  11/11/2018 18:06:05
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TRANSFORMABLE_HPP_
#define GK_TRANSFORMABLE_HPP_

#include <SFML/System/Vector3.hpp>

#include "gk/gl/Transform.hpp"

namespace gk {

class Transformable {
	public:
		virtual ~Transformable() = default;

		void setPosition(float x, float y, float z = 0);
		void setPosition(const sf::Vector3f &position) { setPosition(position.x, position.y, position.z); }

		void setOrigin(float x, float y, float z = 0);
		void setOrigin(const sf::Vector3f &origin) { setOrigin(origin.x, origin.y, origin.z); }

		void setScale(float factorX, float factorY, float factorZ = 1);
		void setScale(const sf::Vector3f &factors) { setScale(factors.x, factors.y, factors.z); }

		void setRotation(float angle) { setRotation(angle, {0, 0, 1}); }
		void setRotation(float angle, const sf::Vector3f &axis);

		const sf::Vector3f& getPosition() const { return m_position; }
		const sf::Vector3f& getOrigin() const { return m_origin; }
		const sf::Vector3f& getScale() const { return m_scale; }
		float getRotation() const { return m_rotation; }

		void move(float offsetX, float offsetY, float offsetZ = 0);
		void move(const sf::Vector3f &offset);

		void scale(float factorX, float factorY, float factorZ = 1);
		void scale(const sf::Vector3f &factor);

		void rotate(float angle);
		void rotate(float angle, const sf::Vector3f &axis);

		const Transform &getTransform() const;
		// const Transform &getInverseTransform() const;

	private:
		sf::Vector3f m_position{0, 0, 0};
		sf::Vector3f m_origin{0, 0, 0};
		sf::Vector3f m_scale{1, 1, 1};
		float m_rotation = 0;

		mutable Transform m_transform;
		// mutable Transform m_inverseTransform;
		mutable Transform m_rotationTransform;

		mutable bool m_transformNeedUpdate = true;
		// mutable bool m_inverseTransformNeedUpdate = true;
};

} // namespace gk

#endif // GK_TRANSFORMABLE_HPP_
