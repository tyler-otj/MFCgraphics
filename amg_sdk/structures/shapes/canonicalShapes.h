#pragma once
#include "shapes.h"

class canonicalShapes{

private:
	canonicalShapes() {}

public:
	static mesh getCanonicalCube() {
		mesh cube;

		cube.tris.reserve(12);
		//South
		cube.tris.emplace_back(triangle{ vec3d{0.0f, 0.0f, 0.0f}, vec3d{0.0f, 1.0f, 0.0f}, vec3d{1.0f, 1.0f, 0.0f} });
		cube.tris.emplace_back(triangle{ vec3d{0.0f, 0.0f, 0.0f}, vec3d{1.0f, 1.0f, 0.0f}, vec3d{1.0f, 0.0f, 0.0f} });
		//East				  					  					  
		cube.tris.emplace_back(triangle{ vec3d{1.0f, 0.0f, 0.0f}, vec3d{1.0f, 1.0f, 0.0f}, vec3d{1.0f, 1.0f, 1.0f} });
		cube.tris.emplace_back(triangle{ vec3d{1.0f, 0.0f, 0.0f}, vec3d{1.0f, 1.0f, 1.0f}, vec3d{1.0f, 0.0f, 1.0f} });
		//North			  					  					  
		cube.tris.emplace_back(triangle{ vec3d{1.0f, 0.0f, 1.0f}, vec3d{1.0f, 1.0f, 1.0f}, vec3d{0.0f, 1.0f, 1.0f} });
		cube.tris.emplace_back(triangle{ vec3d{1.0f, 0.0f, 1.0f}, vec3d{0.0f, 1.0f, 1.0f}, vec3d{0.0f, 0.0f, 1.0f} });
		//West			  					  						  
		cube.tris.emplace_back(triangle{ vec3d{0.0f, 0.0f, 1.0f}, vec3d{0.0f, 1.0f, 1.0f}, vec3d{0.0f, 1.0f, 0.0f} });
		cube.tris.emplace_back(triangle{ vec3d{0.0f, 0.0f, 1.0f}, vec3d{0.0f, 1.0f, 0.0f}, vec3d{0.0f, 0.0f, 0.0f} });
		//Top				  					  					  
		cube.tris.emplace_back(triangle{ vec3d{0.0f, 1.0f, 0.0f}, vec3d{0.0f, 1.0f, 1.0f}, vec3d{1.0f, 1.0f, 1.0f} });
		cube.tris.emplace_back(triangle{ vec3d{0.0f, 1.0f, 0.0f}, vec3d{1.0f, 1.0f, 1.0f}, vec3d{1.0f, 1.0f, 0.0f} });
		//Bottom			  					  					  
		cube.tris.emplace_back(triangle{ vec3d{1.0f, 0.0f, 1.0f}, vec3d{0.0f, 0.0f, 1.0f}, vec3d{0.0f, 0.0f, 0.0f} });
		cube.tris.emplace_back(triangle{ vec3d{1.0f, 0.0f, 1.0f}, vec3d{0.0f, 0.0f, 0.0f}, vec3d{1.0f, 0.0f, 0.0f} });

		return cube;
	}

};