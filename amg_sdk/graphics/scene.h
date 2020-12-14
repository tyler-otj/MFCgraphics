#pragma once
#include "../structures/shapeComponents/mat4x4.h"
#include "../structures/shapeComponents/vec3d.h"
#include "../structures/shapes/shapes.h"

#include <vector>
#include <string>

class scene {
private:
	std::vector<mesh> meshes;

public:
	mat4x4 matProj;
	vec3d camera;
	vec3d lightDirection;

	scene();
	scene(mat4x4 const& projection, vec3d const& cameraVec, vec3d const& lightDir);

	void add_mesh(mesh const& toAdd);
	void add_mesh(std::string const& pathToObjFile);
	std::vector<mesh> const& get_meshes();
};