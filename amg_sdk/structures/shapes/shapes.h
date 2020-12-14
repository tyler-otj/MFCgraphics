#pragma once
#include "shapeBase.h"
#include <fstream>
#include <sstream>

typedef shapeBase<2> line;
typedef shapeBase<3> triangle;

struct mesh {
	std::vector<triangle> tris;

	bool load_object_file(std::string const& fileName) {
		std::ifstream f(fileName);
		if (!f.is_open()) {
			return false;
		}

		std::vector<vec3d> vertices;

		while (!f.eof()) {
			char line[128]; //TODO: find a better size for line
			f.getline(line, 128);

			std::stringstream ss;
			ss << line;

			char firstChar;
			if (line[0] == 'v') {
				vec3d v;
				ss >> firstChar >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			} else if (line[0] == 'f') {
				int f[3];
				ss >> firstChar >> f[0] >> f[1] >> f[2];
				tris.push_back( { vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] } );
			}
		}

		return true;
	}
};