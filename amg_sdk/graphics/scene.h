#pragma once
#include "../structures/shapeComponents/mat4x4.h"
#include "../structures/shapeComponents/vec3d.h"

class Scene {
private:

public:
	Scene();
	Scene(mat4x4 const& projection, vec3d const& cameraVec, vec3d const& lightDir);

	mat4x4 matProj;
	vec3d camera;
	vec3d lightDirection;
};