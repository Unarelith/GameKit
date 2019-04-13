/*
 * =====================================================================================
 *
 *       Filename:  TextureLoader.cpp
 *
 *    Description:
 *
 *        Created:  16/03/2019 18:31:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/core/XMLFile.hpp"
#include "gk/gl/Texture.hpp"
#include "gk/resource/ResourceHandler.hpp"
#include "gk/resource/TextureLoader.hpp"

namespace gk {

void TextureLoader::load(const char *xmlFilename, ResourceHandler &handler) {
	XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *textureElement = doc.FirstChildElement("textures").FirstChildElement("texture").ToElement();
	while (textureElement) {
		std::string name = textureElement->Attribute("name");
		std::string path = textureElement->Attribute("path");

		auto &texture = handler.add<Texture>("texture-" + name);
		texture.loadFromFile(path);

		textureElement = textureElement->NextSiblingElement("texture");
	}
}

}

