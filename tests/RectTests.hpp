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
#ifndef RECTTESTS_HPP_
#define RECTTESTS_HPP_

#include <cxxtest/TestSuite.h>

#include "gk/core/Rect.hpp"

using namespace gk;

class RectTests : public CxxTest::TestSuite  {
	public:
		void testContains() {
			Rect<int> ri{10, 15, 23, 29}; // bottom right corner = 33, 44
			Rect<double> rf{10., 15., 23., 29.};
			TS_ASSERT(ri.contains(10, 15)); // corner
			TS_ASSERT(ri.contains(10, 16)); // left edge
			TS_ASSERT(ri.contains(11, 15)); // top edge
			TS_ASSERT(ri.contains(32, 43)); // near bottom right but still inside

			TS_ASSERT(!ri.contains(33, 43)); // right edge is excluded
			TS_ASSERT(!ri.contains(32, 44)); // bottom edge is excluded
			TS_ASSERT(!ri.contains(33, 44)); // bottom right corner is excluded
			TS_ASSERT(!ri.contains( 9, 16)); // left of left edge is excluded
			TS_ASSERT(!ri.contains(11, 14)); // above top edge is excluded
			TS_ASSERT(!ri.contains(34, 16)); // some other points
			TS_ASSERT(!ri.contains(11, 45));

			TS_ASSERT(rf.contains(10., 15.)); // corner
			TS_ASSERT(rf.contains(10., 16.)); // left edge
			TS_ASSERT(rf.contains(11., 15.)); // top edge
			TS_ASSERT(rf.contains(32.99, 43.99)); // near bottom right but still inside

			TS_ASSERT(!rf.contains(33., 43.)); // right edge is excluded
			TS_ASSERT(!rf.contains(32., 44.)); // bottom edge is excluded
			TS_ASSERT(!rf.contains(33., 44.)); // bottom right corner is excluded
			TS_ASSERT(!rf.contains( 9., 16.)); // left of left edge is excluded
			TS_ASSERT(!rf.contains(11., 14.)); // above top edge is excluded
			TS_ASSERT(!rf.contains(34., 16.)); // some other points
			TS_ASSERT(!rf.contains(11., 45.));
		}

		void testIntersects() {
			using RD = Rect<double>;
			RD r1{10., 15., 23., 29.};
			TS_ASSERT(!r1.intersects(RD{0., 0., 5., 5.})); // not even touching
			TS_ASSERT(!r1.intersects(RD{0., 0., 10.0, 15.0})); // touches top left corner; touching is not intersecting
			TS_ASSERT(!r1.intersects(RD{0., 0., 10.1, 15.0})); // touches top edge
			TS_ASSERT(!r1.intersects(RD{0., 0., 10.0, 15.1})); // touches left edge
			TS_ASSERT( r1.intersects(RD{0., 0., 10.1, 15.1})); // now this is penetrating the other
			TS_ASSERT( r1.intersects(RD{0., 0., 100., 150.})); // one is inside the other
			TS_ASSERT( r1.intersects(RD{0., 0., 100., 15.1})); // making a T shape
			TS_ASSERT( r1.intersects(RD{11., 0., 10., 150.})); // making a + shape

			TS_ASSERT(!r1.intersects(RD{33., 44., 10., 15.}));  // touches bottom right corner
			TS_ASSERT(!r1.intersects(RD{32., 44., 10., 15.}));  // touches bottom edge
			TS_ASSERT(!r1.intersects(RD{33., 43., 10., 15.}));  // touches right edge
			TS_ASSERT(!r1.intersects(RD{33., 42., 10., 1.}));   // touches right edge
			TS_ASSERT( r1.intersects(RD{32., 43.5, 10., 15.})); // penetrating each other
			TS_ASSERT( r1.intersects(RD{32.5, 43., 10., 15.})); // penetrating each other
			TS_ASSERT( r1.intersects(RD{30., 40., 2., 1.}));    // engulfing the rectangle
			TS_ASSERT( r1.intersects(RD{22., 42., 3., 15.}));   // T shape
			TS_ASSERT( r1.intersects(RD{22., 5., 10., 45.}));   // + shape

			// These are explicitly mentioned in the docs
			TS_ASSERT(!gk::IntRect(0, 0, 1, 1).intersects(gk::IntRect(1, 1, 1, 1)));
			TS_ASSERT(!gk::IntRect(1, 1, 1, 1).intersects(gk::IntRect(0, 0, 1, 1)));
		}

		void testIntersection() {
			using RD = Rect<double>;
			RD zero{0., 0., 0., 0.};
			RD r1{10., 15., 23., 29.};
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 5., 5.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 10., 15.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 11., 15.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 10., 16.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 11., 16.}), (RD{10., 15., 1., 1.}));
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 100., 150.}), (RD{10., 15., 23., 29.}));
			TS_ASSERT_EQUALS(r1.intersection(RD{0., 0., 100., 16.}), (RD{10., 15., 23., 1.}));
			TS_ASSERT_EQUALS(r1.intersection(RD{11., 0., 10., 150.}), (RD{11., 15., 10., 29.}));

			TS_ASSERT_EQUALS(r1.intersection(RD{33., 44., 10., 15.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{32., 44., 10., 15.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{33., 43., 10., 15.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{33., 42., 10.,  1.}), zero);
			TS_ASSERT_EQUALS(r1.intersection(RD{32., 43.5, 10., 15.}), (RD{32., 43.5, 1., 0.5}));
			TS_ASSERT_EQUALS(r1.intersection(RD{32.5, 43., 10., 15.}), (RD{32.5, 43., 0.5, 1.}));
			TS_ASSERT_EQUALS(r1.intersection(RD{30., 40., 2., 1.}),   (RD{30., 40., 2., 1.}));
			TS_ASSERT_EQUALS(r1.intersection(RD{22., 42., 3., 15.}),  (RD{22., 42., 3., 2.}));
			TS_ASSERT_EQUALS(r1.intersection(RD{22., 5., 10., 45.}),  (RD{22., 15., 10., 29.}));
		}

		void testIntersectionDirection() {
			using RD = Rect<double>;
			RD r1{10., 15., 23., 29.};
			TS_ASSERT(!r1.intersectionDirection(RD{0., 0., 5., 5.})); // not even touching
			TS_ASSERT(!r1.intersectionDirection(RD{0., 0., 10.0, 15.0})); // touches top left corner; touching is not intersecting
			TS_ASSERT(!r1.intersectionDirection(RD{0., 0., 10.1, 15.0})); // touches top edge
			TS_ASSERT(!r1.intersectionDirection(RD{0., 0., 10.0, 15.1})); // touches left edge
			TS_ASSERT_EQUALS(r1.intersectionDirection(RD{0., 0., 11., 15.1}), 2); // closer on the top
			TS_ASSERT_EQUALS(r1.intersectionDirection(RD{0., 0., 100., 150.}), 1); // closer on the left
			TS_ASSERT_EQUALS(r1.intersectionDirection(RD{0., 0., 100., 15.1}), 2); // making a T shape, closer on the top
			TS_ASSERT_EQUALS(r1.intersectionDirection(RD{11., 0., 10., 150.}), 1); // making a + shape, smaller horizontally

			TS_ASSERT(!r1.intersectionDirection(RD{33., 44., 10., 15.})); // touches bottom right corner
			TS_ASSERT(!r1.intersectionDirection(RD{32., 44., 10., 15.})); // touches bottom edge
			TS_ASSERT(!r1.intersectionDirection(RD{33., 43., 10., 15.})); // touches right edge
			TS_ASSERT(!r1.intersectionDirection(RD{33., 42., 10., 1.}));  // touches right edge
			TS_ASSERT_EQUALS( r1.intersectionDirection(RD{32., 43.9, 10., 15.}), 2); // closer on the bottom
			TS_ASSERT_EQUALS( r1.intersectionDirection(RD{32.9, 43., 10., 15.}), 1); // closer on the right
			TS_ASSERT_EQUALS( r1.intersectionDirection(RD{30., 40., 2., 1.}), 2);    // engulfing the rectangle
			TS_ASSERT_EQUALS( r1.intersectionDirection(RD{22., 42., 3., 15.}), 2);   // T shape
			TS_ASSERT_EQUALS( r1.intersectionDirection(RD{22., 5., 10., 45.}), 1);   // + shape
		}
};

#endif // RECTTESTS_HPP_
