/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#ifndef GK_MOVEMENT_HPP_
#define GK_MOVEMENT_HPP_

#include "gk/scene/SceneObject.hpp"

namespace gk {

class Movement {
	public:
		virtual ~Movement() = default;

		bool isFinished() const { return m_isFinished; }

		virtual void process(SceneObject &object) = 0;

	protected:
		bool m_isFinished = false;
};

} // namespace gk

#endif // GK_MOVEMENT_HPP_
