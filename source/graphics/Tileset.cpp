/*
 * =====================================================================================
 *
 *  GameKit
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2020 the GameKit contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of GameKit.
 *
 *  GameKit is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  GameKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GameKit; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include <sstream>

#include "gk/core/Exception.hpp"
#include "gk/core/XMLFile.hpp"
#include "gk/graphics/Tileset.hpp"

namespace gk {

Tileset::Tileset(const std::string &filename, const std::string &configFile) {
	load(filename, configFile);
}

void Tileset::load(const std::string &filename, const std::string &configFile) {
	Texture::loadFromFile(filename);

	XMLFile doc(configFile);

	tinyxml2::XMLElement *tilesetElement = doc.FirstChildElement("tileset").ToElement();
	if (!tilesetElement)
		throw EXCEPTION("Invalid tileset:", configFile);

	std::string name = tilesetElement->Attribute("name");

	m_tileWidth = tilesetElement->UnsignedAttribute("tilewidth");
	m_tileHeight = tilesetElement->UnsignedAttribute("tileheight");

	u16 tileCount = tilesetElement->UnsignedAttribute("tilecount");
	m_tiles.resize(tileCount, Tile{0});

	tinyxml2::XMLElement *tileElement = tilesetElement->FirstChildElement("tile");
	while (tileElement) {
		u16 tileID = tileElement->UnsignedAttribute("id");
		u16 tileType = tileElement->UnsignedAttribute("type");

		Tile tile{tileType};

		tinyxml2::XMLElement *animationElement = tileElement->FirstChildElement("animation");
		if (animationElement) {
			tinyxml2::XMLElement *frameElement = animationElement->FirstChildElement("frame");
			while (frameElement) {
				u16 frameTileID = frameElement->UnsignedAttribute("tileid");
				u16 frameDuration = frameElement->UnsignedAttribute("duration");

				tile.addAnimationFrame(frameTileID, frameDuration);

				frameElement = frameElement->NextSiblingElement("frame");
			}
		}

		m_info.push_back(tileType);
		setTile(tileID, tile);

		tileElement = tileElement->NextSiblingElement("tile");
	}
}

} // namespace gk

