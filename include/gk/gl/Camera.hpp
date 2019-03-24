/*
 * =====================================================================================
 *
 *       Filename:  Camera.hpp
 *
 *    Description:
 *
 *        Created:  26/12/2018 16:33:40
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_CAMERA_HPP_
#define GK_CAMERA_HPP_

#include <SFML/System/Vector3.hpp>

#include "gk/gl/View.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief 3D camera that defines what is shown on screen
///
/// Code inspired by SFML `3dee`
///
////////////////////////////////////////////////////////////
class Camera : public View {
	public:
		Camera(float fov, float near, float far);
		virtual ~Camera() = default;

		const sf::Vector3f &getPosition() const override { return m_position; }
		const sf::Vector3f &getDirection() const { return m_direction; }
		const sf::Vector3f &getUpVector() const { return m_upVector; }

		float getFieldOfView() const { return m_fieldOfView; }
		float getAspectRatio() const { return m_aspect; }
		float getNearClippingPlane() const { return m_nearPlane; }
		float getFarClippingPlane() const { return m_farPlane; }

		void setPosition(float x, float y, float z) { setPosition(sf::Vector3f{x, y, z}); }
		void setPosition(const sf::Vector3f &position);

		void setDirection(float x, float y, float z) { setDirection(sf::Vector3f{x, y, z}); }
		void setDirection(const sf::Vector3f &direction);

		void setTargetPosition(float x, float y, float z) { setTargetPosition(sf::Vector3f{x, y, z}); }
		void setTargetPosition(const sf::Vector3f &target);

		void setUpVector(float x, float y, float z) { setUpVector(sf::Vector3f{x, y, z}); }
		void setUpVector(const sf::Vector3f &upVector);

		void setFieldOfView(float fov);
		void setAspectRatio(float aspect);
		void setNearClippingPlane(float distance);
		void setFarClippingPlane(float distance);

		const Transform &getTransform() const override;
		const Transform &getViewTransform() const override;

	private:
		sf::Vector3f m_position{0, 0, 0};
		sf::Vector3f m_direction{0, 0, -1};
		sf::Vector3f m_upVector{0, 1, 0};

		float m_fieldOfView = 90.0f;
		float m_aspect = 1.0f;
		float m_nearPlane = 0.1f;
		float m_farPlane = 1000.0f;
};

} // namespace gk

#endif // GK_CAMERA_HPP_
