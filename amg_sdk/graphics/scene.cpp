#include "Scene.h"

scene::scene() {}

scene::scene(mat4x4 const& projection, vec3d const& cameraVec, vec3d const& lightDir) :
	matProj(projection), camera(cameraVec), lightDirection(lightDir),
	meshes(0)
	{}

void scene::add_mesh(mesh const& toAdd) {
	meshes.push_back(toAdd);
}