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
#ifndef GK_EASYCONTROLLER_HPP_
#define GK_EASYCONTROLLER_HPP_

#include <functional>

#include "gk/scene/controller/AbstractController.hpp"

namespace gk {

class EasyController : public AbstractController {
	using Function = std::function<void(SceneObject &object)>;

	public:
		EasyController(const Function &func) : m_func(func) {}

		void update(SceneObject &object) override {
			m_func(object);
		}

	private:
		Function m_func;
};

} // namespace gk

#endif // GK_EASYCONTROLLER_HPP_
