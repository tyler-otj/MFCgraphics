#include "vec3d.h"

vec3d vec3d::operator+(float const& f) const {
	return vec3d{ x + f, y + f, z + f };
}

vec3d vec3d::operator+(vec3d const& other) const {
	return vec3d{ x + other.x, y + other.y, z + other.z };
}

vec3d vec3d::operator-(vec3d const& other) const {
	return vec3d{ x - other.x, y - other.y, z - other.z };
}

vec3d vec3d::operator*(float const f) const {
	return vec3d{ x * f, y * f, z * f }; return vec3d();
}

void vec3d::operator/=(float const f) {
	x /= f;
	y /= f;
	z /= f;
}

void vec3d::operator+=(vec3d const& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

void vec3d::operator+=(float const f) {
	x += f;
	y += f;
	z += f;
}

void vec3d::normalize() {
	float const magnitude = sqrtf(x*x + y * y + z * z);
	*this /= magnitude;
}

void vec3d::multByMatrix(mat4x4 const& m) {
	x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + m.m[3][0];
	y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + m.m[3][1];
	z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + m.m[3][2];
	float const w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + m.m[3][3];

	if (w != 0) {
		x /= w;
		y /= w;
		z /= w;
	}
}

//TODO
void vec3d::scaleIntoView(float const screenWidth, float const screenHeight) {
	//*this += 1.0f;

	//x *= 0.5f * screenWidth;
	//y *= 0.5f * screenHeight;
	//x *= 0.5f * screenWidth;
	//y *= 0.5f * screenHeight;
	//x *= 0.5f * screenWidth;
	//y *= 0.5f * screenHeight;
}

float vec3d::dotProduct(vec3d const& other) {
	return x * other.x + y * other.y + z * other.z;
}

vec3d vec3d::getVecMultByMatrix(mat4x4 const& m) const {
	vec3d reply = { 1.0f, 1.0f, 1.0f };

	reply.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + m.m[3][0];
	reply.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + m.m[3][1];
	reply.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + m.m[3][2];
	float const w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		reply.x /= w;
		reply.y /= w;
		reply.z /= w;
	}

	return reply;
}