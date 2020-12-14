#include "Scene.h"

scene::scene() {}

scene::scene(mat4x4 const& projection, vec3d const& cameraVec, vec3d const& lightDir) :
	matProj(projection), camera(cameraVec), lightDirection(lightDir),
	meshes(0)
	{}

void scene::add_mesh(mesh const& toAdd) {
	meshes.push_back(toAdd);
}

void scene::add_mesh(std::string const& pathToObjFile) {
	mesh toLoad;

	if (!toLoad.load_object_file(pathToObjFile)) {
		throw std::runtime_error("Unable to load object file");
	}
	meshes.push_back(std::move(toLoad));
}

std::vector<mesh> const& scene::get_meshes() {
	return meshes;
}