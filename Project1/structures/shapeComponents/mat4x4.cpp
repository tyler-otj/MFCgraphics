#include "mat4x4.h"

mat4x4 mat4x4::dotProduct(mat4x4 const& other) const {
	mat4x4 reply;

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			reply.m[row][col] = m[row][0] * other.m[0][col] + m[row][1] * other.m[1][col] + m[row][2] * other.m[2][col] + m[row][3] * other.m[3][col];
		}
		    //reply.m[row][0] = m[row][0] * other.m[0][0] + m[row][1] * other.m[1][0] + m[row][2] * other.m[2][0] + m[row][3] * other.m[3][0];
		    //reply.m[row][1] = m[row][0] * other.m[0][1] + m[row][1] * other.m[1][1] + m[row][2] * other.m[2][1] + m[row][3] * other.m[3][1];
		    //reply.m[row][2] = m[row][0] * other.m[0][2] + m[row][1] * other.m[1][2] + m[row][2] * other.m[2][2] + m[row][3] * other.m[3][2];
		    //reply.m[row][3] = m[row][0] * other.m[0][3] + m[row][1] * other.m[1][3] + m[row][2] * other.m[2][3] + m[row][3] * other.m[3][3];
	}

	return reply;
}

mat4x4 mat4x4::rotateZ(float const theta) {
	mat4x4 reply;
	reply.m[0][0] = cosf(theta);
	reply.m[0][1] = sinf(theta);
	reply.m[1][0] = -sinf(theta);
	reply.m[1][1] = cosf(theta);
	reply.m[2][2] = 1;
	reply.m[3][3] = 1;
	return reply;
}

mat4x4 mat4x4::rotateX(float const theta, float const rotationSpeed) {
	mat4x4 reply;
	reply.m[0][0] = 1;
	reply.m[1][1] = cosf(theta * rotationSpeed);
	reply.m[1][2] = sinf(theta * rotationSpeed);
	reply.m[2][1] = -sinf(theta * rotationSpeed);
	reply.m[2][2] = cosf(theta * rotationSpeed);
	reply.m[3][3] = 1;
	return reply;
}

mat4x4 mat4x4::rotateY(float const theta, float const rotationSpeed) {
	mat4x4 reply;
	reply.m[0][0] = cosf(theta * rotationSpeed);
	reply.m[0][2] = -sinf(theta * rotationSpeed);
	reply.m[1][1] = 1;
	reply.m[2][0] = sinf(theta * rotationSpeed);
	reply.m[2][2] = cosf(theta  * rotationSpeed);
	reply.m[3][3] = 1;
	return reply;
}

const mat4x4 mat4x4::projection(float const aspectRatio, float const fovRad, float const far, float const near) {
	mat4x4 reply;
	reply.m[0][0] = aspectRatio * fovRad;
	reply.m[1][1] = fovRad;
	reply.m[2][2] = far / (far - near);
	reply.m[3][2] = (-far * near) / (far - near);
	reply.m[2][3] = 1.0f;
	reply.m[3][3] = 1.0f;
	return reply;
}