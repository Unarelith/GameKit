/*
 * =====================================================================================
 *
 *       Filename:  Image.cpp
 *
 *    Description:
 *
 *        Created:  20/09/2014 16:22:12
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "gk/gl/Texture.hpp"
#include "gk/gl/Vertex.hpp"
#include "gk/gui/Image.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

Image::Image(const std::string &textureName) {
	load(ResourceHandler::getInstance().get<Texture>(textureName));
}

Image::Image(const Texture &texture) {
	load(texture);
}

void Image::load(const Image &image) {
	m_texture = image.m_texture;

	m_width = image.m_width;
	m_height = image.m_height;

	m_clipRect = image.m_clipRect;

	m_color = image.m_color;

	updateVertexBuffer();
}

void Image::load(const std::string &textureName) {
	load(ResourceHandler::getInstance().get<Texture>(textureName));
}

void Image::load(const Texture &texture) {
	m_texture = &texture;

	m_width = m_texture->width();
	m_height = m_texture->height();

	setClipRect(0, 0, m_width, m_height);
}

void Image::setClipRect(float x, float y, u16 width, u16 height) {
	m_clipRect.reset(x, y, width, height);

	updateVertexBuffer();
}

void Image::updateVertexBuffer() const {
	Vertex vertices[4] = {
		{{m_clipRect.width, 0,                 0, -1}},
		{{0,                0,                 0, -1}},
		{{0,                m_clipRect.height, 0, -1}},
		{{m_clipRect.width, m_clipRect.height, 0, -1}},
	};

	FloatRect texRect{
		m_clipRect.x / float(m_width),
		m_clipRect.y / float(m_height),
		m_clipRect.width / float(m_width),
		m_clipRect.height / float(m_height)
	};

	vertices[0].texCoord[0] = texRect.x + texRect.width;
	vertices[0].texCoord[1] = texRect.y;
	vertices[1].texCoord[0] = texRect.x;
	vertices[1].texCoord[1] = texRect.y;
	vertices[2].texCoord[0] = texRect.x;
	vertices[2].texCoord[1] = texRect.y + texRect.height;
	vertices[3].texCoord[0] = texRect.x + texRect.width;
	vertices[3].texCoord[1] = texRect.y + texRect.height;

	for (u8 i = 0 ; i < 4 ; ++i) {
		vertices[i].color[0] = m_color.r;
		vertices[i].color[1] = m_color.g;
		vertices[i].color[2] = m_color.b;
		vertices[i].color[3] = m_color.a;
	}

	VertexBuffer::bind(&m_vbo);
	m_vbo.setData(sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	VertexBuffer::bind(nullptr);
}

void Image::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();

	states.texture = m_texture;
	states.vertexAttributes = VertexAttribute::Only2d;

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	static const GLubyte indices[] = {
		0, 1, 3,
		3, 1, 2
	};

	target.drawElements(m_vbo, GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices, states);
	// target.draw(m_vbo, GL_QUADS, 0, 4, states);
}

}

