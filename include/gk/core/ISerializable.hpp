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
#ifndef GK_ISERIALIZABLE_HPP_
#define GK_ISERIALIZABLE_HPP_

namespace sf { class Packet; }

namespace gk {

class ISerializable {
	public:
		virtual ~ISerializable() = default;

		virtual void serialize(sf::Packet &) const {};
		virtual void deserialize(sf::Packet &) {};
};

} // namespace gk

sf::Packet &operator<<(sf::Packet &packet, const gk::ISerializable &s);
sf::Packet &operator>>(sf::Packet &packet, gk::ISerializable &s);

#endif // GK_ISERIALIZABLE_HPP_
