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

#include <array>

#include "gk/graphics/Color.hpp"
#include "gk/gl/IDrawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

class RectangleShape : public IDrawable, public Transformable {
	public:
		RectangleShape();
		RectangleShape(float width, float height, const Color &color = Color::White);

		const Color &color() const { return m_color; }
		void setColor(const Color &color) { m_color = color; updateVertexBuffer(); }

		void setWireframeMode(bool wireframeMode) { m_wireframeMode = wireframeMode; }

		float width() const { return m_width; }
		float height() const { return m_height; }

		Vector2f getSize() const { return Vector2f{m_width, m_height}; }

		void setSize(float width, float height) { m_width = width; m_height = height; updateVertexBuffer(); }

		void setOutlineColor(const Color &color) { m_outlineColor = color; updateVertexBuffer(); }
		void setOutlineThickness(int outlineThickness) { m_outlineThickness = outlineThickness; updateVertexBuffer(); }

	private:
		void updateVertexBuffer() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		Color m_color;

		bool m_wireframeMode = false;

		float m_width = 0;
		float m_height = 0;

		VertexBuffer m_vbo;

		Color m_outlineColor{Color::White};
		int m_outlineThickness = 0;

		std::array<GLubyte, 6 * 5> m_indices{
			0, 1, 3,
			3, 1, 2
		};
};

} // namespace gk

#endif // GK_RECTANGLESHAPE_HPP_
