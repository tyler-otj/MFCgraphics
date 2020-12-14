#include "Scene.h"

Scene::Scene() {}

Scene::Scene(mat4x4 const& projection, vec3d const& cameraVec, vec3d const& lightDir) 
	: matProj(projection), camera(cameraVec), lightDirection(lightDir) {}