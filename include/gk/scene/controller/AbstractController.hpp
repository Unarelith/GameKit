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
#ifndef GK_ABSTRACTCONTROLLER_HPP_
#define GK_ABSTRACTCONTROLLER_HPP_

#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class AbstractController {
	public:
		virtual ~AbstractController() = default;

		virtual void reset(SceneObject &) {}
		virtual void update(SceneObject &object) = 0;

		virtual void reset(SceneObjectList &objectList) { for(auto &object : objectList) reset(object); }
		virtual void update(SceneObjectList &objectList) { for(auto &object : objectList) update(object); }

		virtual bool isGlobal() const { return false; }
};

} // namespace gk

#endif // GK_ABSTRACTCONTROLLER_HPP_
