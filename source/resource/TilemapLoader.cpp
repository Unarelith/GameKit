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
#include "gk/graphics/Tilemap.hpp"
#include "gk/resource/TilemapLoader.hpp"

namespace gk {

void TilemapLoader::load(const char *xmlFilename, ResourceHandler &handler) {
	XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *mapElement = doc.FirstChildElement("maps").FirstChildElement("map").ToElement();
	while(mapElement) {
		std::string name = mapElement->Attribute("name");
		std::string tilesetName = mapElement->Attribute("tileset");

		Tileset &tileset = handler.get<Tileset>(tilesetName);

		loadMap(name, tileset, handler);

		mapElement = mapElement->NextSiblingElement("map");
	}
}

void TilemapLoader::loadMap(const std::string &name, Tileset &tileset, ResourceHandler &handler) {
	XMLFile doc("resources/maps/" + name + ".tmx");

	tinyxml2::XMLElement *mapElement = doc.FirstChildElement("map").ToElement();

	u16 width = mapElement->IntAttribute("width");
	u16 height = mapElement->IntAttribute("height");

	std::vector<std::vector<u16>> data;
	tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
	while (layerElement) {
		tinyxml2::XMLElement *tileElement = layerElement->FirstChildElement("data")->FirstChildElement("tile");

		std::vector<u16> layer;
		while(tileElement) {
			s16 tileID = tileElement->IntAttribute("gid") - 1;

			layer.push_back((tileID >= 0) ? tileID : 0);

			tileElement = tileElement->NextSiblingElement("tile");
		}

		data.emplace_back(std::move(layer));

		layerElement = layerElement->NextSiblingElement("layer");
	}

	handler.add<Tilemap>("map-" + name, width, height, tileset, data);
}

} // namespace gk

