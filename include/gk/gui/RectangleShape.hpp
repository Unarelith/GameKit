/*
 * =====================================================================================
 *
 *       Filename:  RectangleShape.hpp
 *
 *    Description:
 *
 *        Created:  27/09/2014 17:06:48
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_RECTANGLESHAPE_HPP_
#define GK_RECTANGLESHAPE_HPP_

#include "gk/core/Color.hpp"
#include "gk/gl/IDrawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

class RectangleShape : public IDrawable, public Transformable {
	public:
		RectangleShape() = default;
		RectangleShape(float width, float height, const Color &color = Color::Black);

		const Color &color() const { return m_color; }
		void setColor(const Color &color) { m_color = color; updateVertexBuffer(); }

		void setWireframeMode(bool wireframeMode) { m_wireframeMode = wireframeMode; }

		float width() const { return m_width; }
		float height() const { return m_height; }

		Vector2f getSize() const { return Vector2f{m_width, m_height}; }

		void setSize(float width, float height) { m_width = width; m_height = height; updateVertexBuffer(); }

	private:
		void updateVertexBuffer() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		Color m_color = Color::Black;

		bool m_wireframeMode = false;

		float m_width = 0;
		float m_height = 0;

		VertexBuffer m_vbo;
};

} // namespace gk

#endif // GK_RECTANGLESHAPE_HPP_
