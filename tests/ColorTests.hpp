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
#ifndef COLORTESTS_HPP_
#define COLORTESTS_HPP_

#include <cxxtest/TestSuite.h>

#include "gk/graphics/Color.hpp"

using namespace gk;

class ColorTests : public CxxTest::TestSuite  {
	public:
		void testMix() {
			Color c1 = Color::fromRGBA32(7, 15, 225, 123);
			Color c2 = Color::fromRGBA32(192, 192, 192, 192);
			Color c3;
			TS_ASSERT_EQUALS(c1.mix(c2, 0.0f), c1);
			TS_ASSERT_EQUALS(c1.mix(c2, 1.0f), c2);
			c3.r = (  7/255.f+192/255.f)*0.5f;
			c3.g = ( 15/255.f+192/255.f)*0.5f;
			c3.b = (225/255.f+192/255.f)*0.5f;
			c3.a = (123/255.f+192/255.f)*0.5f;
			TS_ASSERT_EQUALS((c1.mix(c2, 0.5f)), c3);
		}

		// Currently disabled because the current code is buggy
		void xtestAddition() {
			Color c1 = Color::fromRGBA32(7, 15, 225, 123);
			Color c2 = Color::fromRGBA32(192, 192, 192, 192);
			Color c3;
			// Should addition clamp?
			c3.r = (  7/255.f+192/255.f);
			c3.g = ( 15/255.f+192/255.f);
			c3.b = (225/255.f+192/255.f);
			c3.a = (123/255.f+192/255.f);
			TS_ASSERT_EQUALS(c1 + c2, c3);
		}

		void xtestSubtraction() {
			Color c1 = Color::fromRGBA32(7, 15, 225, 123);
			Color c2 = Color::fromRGBA32(192, 192, 192, 192);
			Color c3;
			// Should subtraction clamp?
			c3.r = (  7/255.f-192/255.f);
			c3.g = ( 15/255.f-192/255.f);
			c3.b = (225/255.f-192/255.f);
			c3.a = (123/255.f-192/255.f);
			TS_ASSERT_EQUALS(c1 - c2, c3);
		}
};

#endif // COLORTESTS_HPP_
