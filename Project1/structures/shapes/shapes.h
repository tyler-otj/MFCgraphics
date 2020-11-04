#pragma once
#include "shapeBase.h"

typedef shapeBase<2> line;
typedef shapeBase<3> triangle;

struct mesh {
	std::vector<triangle> tris;
};




//struct triangle : public shapeBase<3> {
//	triangle(vec3d v1, vec3d v2, vec3d v3) : shapeBase() {
//		vec[0] = v1;
//		vec[1] = v2;
//		vec[2] = v3;
//	}
//};