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
#ifndef VECTOR2TESTS_HPP_
#define VECTOR2TESTS_HPP_

#include <cxxtest/TestSuite.h>

#include "gk/core/Vector2.hpp"

using namespace gk;

class Vector2Tests : public CxxTest::TestSuite  {
	public:
		void testEqual() {
			Vector2i v1{5, 4}, v2{2, 6}, v3{5, 4};

			TS_ASSERT(v1 != v2);
			TS_ASSERT(v1 == v1);
			TS_ASSERT(v1 == v3);
		}

		void testAssignement() {
			Vector2i v1, v2;

			v1 = {2, 6};
			v2 = 0;

			TS_ASSERT_EQUALS(v1, (Vector2i{2, 6}));
			TS_ASSERT_EQUALS(v2, (Vector2i{0, 0}));
		}

		void testAddition() {
			Vector2i v1{5, 4}, v2{2, 6}, v3{2, 3}, v4{4, 8};

			TS_ASSERT_EQUALS(v1 + v2, (Vector2i{ 7, 10}));
			TS_ASSERT_EQUALS(v2 + v3, (Vector2i{ 4,  9}));
			TS_ASSERT_EQUALS(v1 + v1, (Vector2i{10,  8}));

			v4 += v2;

			TS_ASSERT_EQUALS(v4, (Vector2i{ 6, 14}));
		}

		void testSubtraction() {
			Vector2i v1{5, 4}, v2{2, 6}, v3{2, 3}, v4{4, 8};

			TS_ASSERT_EQUALS(v1 - v2, (Vector2i{ 3, -2}));
			TS_ASSERT_EQUALS(v2 - v3, (Vector2i{ 0,  3}));
			TS_ASSERT_EQUALS(v1 - v1, (Vector2i{ 0,  0}));
			TS_ASSERT_EQUALS(v4 - v2, (Vector2i{ 2,  2}));
		}

		void testMultiplication() {
			Vector2i v1{5, -4};

			TS_ASSERT_EQUALS(v1 * -4, (Vector2i{-20, 16}));
			TS_ASSERT_EQUALS( 8 * v1, (Vector2i{40, -32}));
		}

		void testDivision() {
			Vector2i v1{4, -4};

			TS_ASSERT_EQUALS(v1 / -4, (Vector2i{-1, 1}));
			TS_ASSERT_THROWS_ANYTHING(v1 / 0);
		}
};

#endif // VECTOR2TESTS_HPP_
