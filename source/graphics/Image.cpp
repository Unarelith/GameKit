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

#include "gk/gl/GLCheck.hpp"
#include "gk/gl/Vertex.hpp"
#include "gk/graphics/Image.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

Image::Image(const std::string &textureName) {
	load(ResourceHandler::getInstance().get<sf::Texture>(textureName));
}

Image::Image(const sf::Texture &texture) {
	load(texture);
}

void Image::load(const Image &image) {
	m_texture = image.m_texture;

	m_width = image.m_width;
	m_height = image.m_height;

	m_clipRect = image.m_clipRect;
	m_posRect = image.m_posRect;

	m_color = image.m_color;

	updateVertexBuffer();
}

void Image::load(const std::string &textureName) {
	load(ResourceHandler::getInstance().get<sf::Texture>(textureName));
}

void Image::load(const sf::Texture &texture) {
	m_texture = &texture;

	m_width = m_texture->getSize().x;
	m_height = m_texture->getSize().y;

	setClipRect(0, 0, m_width, m_height);
	setPosRect(0, 0, m_width, m_height);
}

void Image::setClipRect(float x, float y, u16 width, u16 height) {
	m_clipRect = sf::FloatRect(x, y, width, height);

	m_posRect.width = width;
	m_posRect.height = height;

	updateVertexBuffer();
}

void Image::setPosRect(float x, float y, u16 width, u16 height) {
	m_posRect = sf::FloatRect(x, y, width, height);

	updateVertexBuffer();
}

void Image::updateVertexBuffer() const {
	Vertex vertices[4] = {
		{{m_posRect.left + m_posRect.width, m_posRect.top,                    0, -1}},
		{{m_posRect.left,                   m_posRect.top,                    0, -1}},
		{{m_posRect.left,                   m_posRect.top + m_posRect.height, 0, -1}},
		{{m_posRect.left + m_posRect.width, m_posRect.top + m_posRect.height, 0, -1}},
	};

	sf::FloatRect texRect{
		m_clipRect.left   / float(m_width),
		m_clipRect.top    / float(m_height),
		m_clipRect.width  / float(m_width),
		m_clipRect.height / float(m_height)
	};

	if (!m_isFlipped) {
		vertices[0].texCoord[0] = texRect.left + texRect.width;
		vertices[0].texCoord[1] = texRect.top;
		vertices[1].texCoord[0] = texRect.left;
		vertices[1].texCoord[1] = texRect.top;
		vertices[2].texCoord[0] = texRect.left;
		vertices[2].texCoord[1] = texRect.top  + texRect.height;
		vertices[3].texCoord[0] = texRect.left + texRect.width;
		vertices[3].texCoord[1] = texRect.top  + texRect.height;
	}
	else {
		vertices[0].texCoord[0] = texRect.left;
		vertices[0].texCoord[1] = texRect.top;
		vertices[1].texCoord[0] = texRect.left + texRect.width;
		vertices[1].texCoord[1] = texRect.top;
		vertices[2].texCoord[0] = texRect.left + texRect.width;
		vertices[2].texCoord[1] = texRect.top  + texRect.height;
		vertices[3].texCoord[0] = texRect.left;
		vertices[3].texCoord[1] = texRect.top + texRect.height;
	}

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

	glCheck(glDisable(GL_CULL_FACE));
	glCheck(glDisable(GL_DEPTH_TEST));

	static const GLubyte indices[] = {
		0, 1, 3,
		3, 1, 2
	};

	target.drawElements(m_vbo, GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices, states);
}

}

