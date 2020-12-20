#include "vec3d.h"
#include "mat4x4.h"

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
	return vec3d{ x * f, y * f, z * f };
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
	x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
	y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
	z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
	w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];

	//TODO: more normalization?!
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

float vec3d::dotProduct(vec3d const& other) const {
	return x * other.x + y * other.y + z * other.z;
}

vec3d vec3d::crossProduct(vec3d const& other) const {
	float const x = y * other.z - z * other.y;
	float const y = z * other.x - x * other.z;
	float const z = x * other.y - y * other.x;

	vec3d reply;
	reply.x = x;
	reply.y = y;
	reply.z = z;

	return reply;
}

vec3d vec3d::getVecMultByMatrix(mat4x4 const& m) const {
	vec3d reply = { 1.0f, 1.0f, 1.0f };

	reply.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
	reply.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
	reply.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
	reply.w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];

	//TODO: what is this and why is it here
	//reply.normalize();
	float const w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		reply.x /= w;
		reply.y /= w;
		reply.z /= w;
	}

	return reply;
}