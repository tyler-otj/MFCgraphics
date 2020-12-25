#pragma once

struct mat4x4;

struct vec3d {
	float x = 0;
	float y = 0; 
	float z = 0;
	float w = 1;

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
	float dotProduct(vec3d const& other) const;
	vec3d crossProduct(vec3d const& other) const;
	vec3d getVecMultByMatrix(mat4x4 const& m) const;
	float length() const;
};