#pragma once
#include "mat4x4.h"

struct vec3d {
	float x, y, z;

	vec3d operator+(float const& f) const;
	vec3d operator+(vec3d const& other) const;
	vec3d operator-(vec3d const& other) const;
	vec3d operator*(float const f) const;
	void operator/=(float const f);
	void operator+=(vec3d const& other);
	void operator+=(float const f);

	void normalize();
	void multByMatrix(mat4x4 const& m);
	void scaleIntoView(float const screenWidth, float const screenHeight);
	float dotProduct(vec3d const& other);
	vec3d getVecMultByMatrix(mat4x4 const& m) const;
};