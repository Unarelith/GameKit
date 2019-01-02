/*
 * =====================================================================================
 *
 *       Filename:  View.cpp
 *
 *    Description:
 *
 *        Created:  01/01/2019 21:30:43
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <cmath>

#include "gk/gl/View.hpp"

namespace gk {

View::View() {
	reset(FloatRect(0, 0, 1000, 1000));
}

View::View(const Vector3f &center, const Vector2f &size) {
	reset(FloatRect(center.xy(), size));
}

View::View(const FloatRect &rectangle) {
	reset(rectangle);
}

void View::setCenter(float x, float y, float z) {
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	m_viewTransformUpdated = false;
}

void View::setSize(float width, float height) {
	m_size.x = width;
	m_size.y = height;

	m_transformUpdated = false;
	m_viewTransformUpdated = false;
}

void View::setRotation(float angle) {
	m_rotation = static_cast<float>(fmod(angle, 360));
	if (m_rotation < 0)
		m_rotation += 360.f;

	m_viewTransformUpdated = false;
}

void View::reset(const FloatRect &rectangle) {
	m_position.x = rectangle.x + rectangle.width / 2.f;
	m_position.y = rectangle.y + rectangle.height / 2.f;

	m_size.x = rectangle.width;
	m_size.y = rectangle.height;

	m_rotation = 0;

	m_transformUpdated = false;
}

void View::move(float offsetX, float offsetY, float offsetZ) {
	setCenter(m_position.x + offsetX, m_position.y + offsetY, m_position.z + offsetZ);
}

const Transform &View::getTransform() const {
	if (!m_transformUpdated) {
		m_transform = glm::ortho(0.0f, m_size.x, m_size.y, 0.0f);

		m_transformUpdated = true;
	}

	return m_transform;
}

const Transform &View::getViewTransform() const {
	if (!m_viewTransformUpdated) {
		Transform positionTransform;
		positionTransform.translate(m_size.x / 2.f - m_position.x, m_size.y / 2.f - m_position.y);

		Transform rotationTransform;
		rotationTransform.rotate(m_rotation * M_PI / 180.0f);

		m_viewTransform = positionTransform * rotationTransform;

		// m_viewTransform = Transform::Identity;
		// m_viewTransform.rotate(m_rotation);
		// m_viewTransform.translate(Vector3f{getCenter().x, getCenter().y, 0}
		// 		- Vector3f{getSize(), 0.f} / 2.0f);

		m_viewTransformUpdated = true;
	}

	return m_viewTransform;
}

} // namespace gk

