#include "Scene.h"

scene::scene() {}

scene::scene(mat4x4 const& projection, vec3d const& cameraVec, vec3d const& lightDir) :
	matProj(projection), lightDirection(lightDir), meshes(0)
{
	vec3d up = {0, 1, 0};
	vec3d camera;
	vec3d lookDir = {0, 0, 1};
	vec3d target = camera + lookDir;
	mat4x4 matCamera = mat4x4::pointAt(camera, target, up);
	view = mat4x4::inverse(matCamera);
}

void scene::add_mesh(mesh const& toAdd) {
	meshes.push_back(toAdd);
}

void scene::add_mesh(std::string const& pathToObjFile) {
	mesh toLoad;

	if (!toLoad.load_object_file(pathToObjFile)) {
		throw std::runtime_error("Unable to load object file at " + pathToObjFile);
	}
	meshes.push_back(std::move(toLoad));
}

std::vector<mesh> const& scene::get_meshes() {
	return meshes;
}