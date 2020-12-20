#pragma once
#include <math.h>
#include "vec3d.h"

struct mat4x4 {
	float m[4][4] = { 0 };

	mat4x4() : m{ 0 } {}

	mat4x4 dotProduct(mat4x4 const& other) const;

	static mat4x4 rotateZ(float const theta);
	static mat4x4 rotateX(float const theta, float const rotationSpeed = 0.5f);
	static mat4x4 rotateY(float const theta, float const rotationSpeed = 0.5f);
	static const mat4x4 projection(float const aspectRatio, float const fovRad, float const far, float const near);
	static mat4x4 pointAt(vec3d const& pos, vec3d const& target, vec3d const& up);
	static mat4x4 inverse(mat4x4 const& m);
};