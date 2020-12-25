#include "mat4x4.h"

mat4x4 mat4x4::dotProduct(mat4x4 const& other) const {
	mat4x4 reply;

	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			reply.m[row][col] = m[row][0] * other.m[0][col] + m[row][1] * other.m[1][col] + m[row][2] * other.m[2][col]; // + m[row][3] * other.m[3][col]; //TODO?
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

mat4x4 mat4x4::pointAt(vec3d const& pos, vec3d const& target, vec3d const& up) {
	vec3d newForward = target - pos;
	newForward.normalize();
	
	vec3d a = newForward * up.dotProduct(newForward);
	vec3d newUp = up - a;
	newUp.normalize();

	//vec3d newRight = newUp.crossProduct(newForward);
	vec3d newRight = newForward.crossProduct(newUp);

	//dimensioning and translation matrix
	mat4x4 matrix;
	matrix.m[0][0] = newRight.x;
	matrix.m[0][1] = newRight.y;
	matrix.m[0][2] = newRight.z;
	matrix.m[0][3] = 0.0f;

	matrix.m[1][0] = newUp.x;
	matrix.m[1][1] = newUp.y;
	matrix.m[1][2] = newUp.z;
	matrix.m[1][3] = 0.0f;

	matrix.m[2][0] = newForward.x;
	matrix.m[2][1] = newForward.y;
	matrix.m[2][2] = newForward.z;
	matrix.m[2][3] = 0.0f;

	matrix.m[3][0] = pos.x;
	matrix.m[3][1] = pos.y;
	matrix.m[3][2] = pos.z;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

// Only for Rotation/Translation Matrices
// "look at" matrix
mat4x4 mat4x4::inverse(mat4x4 const& m){
	mat4x4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}