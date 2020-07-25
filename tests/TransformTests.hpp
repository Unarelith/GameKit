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
#ifndef TRANSFORMTESTS_HPP_
#define TRANSFORMTESTS_HPP_

#include <cxxtest/TestSuite.h>

#include "gk/gl/Transform.hpp"

bool within(float a, float b, float tol) {
	return fabsf(a - b) <= tol;
}

bool within(const glm::mat4 m1, const glm::mat4 m2, float tol) {
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j) {
		if (!within(m1[i][j], m2[i][j], tol))
			return false;
	}
	return true;
}

#define DEG_TO_RADf (3.1415927f/180.f)
#define c30 sqrtf(.75f)
#define s30 0.5f
#define c15 ((sqrtf(6.f)+sqrtf(2.f))/4.f)
#define s15 ((sqrtf(6.f)-sqrtf(2.f))/4.f)

class TransformTests : public CxxTest::TestSuite  {
	public:
		void testRotate() {
			{
				Transform t;
				glm::mat4 m{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
				TS_ASSERT(within(t.getMatrix(), m, 0));
			}

			{
				Transform t;
				t.rotateX(30);
				glm::mat4 m{1,0,0,0, 0,c30,s30,0, 0,-s30,c30,0, 0,0,0,1};
				TS_ASSERT(within(t.getMatrix(), m, 1e-6f));

				Transform t2;
				t2.rotate(30, {1,0,0});
				TS_ASSERT(within(t2.getMatrix(), m, 1e-6f));
			}

			{
				Transform t;
				t.rotateY(30);
				glm::mat4 m{c30,0,-s30,0, 0,1,0,0, s30,0,c30,0, 0,0,0,1};
				TS_ASSERT(within(t.getMatrix(), m, 1e-6f));

				Transform t2;
				t2.rotate(30, {0,1,0});
				TS_ASSERT(within(t2.getMatrix(), m, 1e-6f));
			}

			{
				Transform t;
				t.rotateZ(30);
				glm::mat4 m{c30,s30,0,0, -s30,c30,0,0, 0,0,1,0, 0,0,0,1};
				TS_ASSERT(within(t.getMatrix(), m, 1e-6f));

				Transform t2;
				t2.rotate(30, {0,0,1});
				TS_ASSERT(within(t2.getMatrix(), m, 1e-6f));
			}

			{
				Transform t;
				t.lrotateX(30);
				t.lrotateY(15);
				glm::mat4 m{c15,0,-s15,0, s30*s15,c30,c15*s30,0, c30*s15,-s30,c15*c30,0, 0,0,0,1};
				TS_ASSERT(within(t.getMatrix(), m, 1e-6f));

				Transform t2;
				t2.rotate(15, {0,1,0});
				t2.rotate(30, {1,0,0});
				TS_ASSERT(within(t2.getMatrix(), m, 1e-6f));
			}

			{
				Transform t, t1, t2;
				t.lrotateX(30);
				t.lrotateY(25);
				t.lrotateZ(23);
				t.lrotateX(21);

				t1.rotateX(21);
				t1.rotateZ(23);
				t1.rotateY(25);
				t1.rotateX(30);

				TS_ASSERT(within(t.getMatrix(), t1.getMatrix(), 0));

				t2.rotate(21, {1,0,0});
				t2.rotate(23, {0,0,1});
				t2.rotate(25, {0,1,0});
				t2.rotate(30, {1,0,0});

				TS_ASSERT(within(t.getMatrix(), t2.getMatrix(), 1e-5f));
			}
		}
};

#endif // TRANSFORMTESTS_HPP_
