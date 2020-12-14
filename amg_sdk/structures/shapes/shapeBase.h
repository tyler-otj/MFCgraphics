#pragma once
#include <vector>
#include "../shapeComponents/vec3d.h"

template<size_t NumEdges>
struct shapeBase {
	vec3d vec[NumEdges];
	short color;

	void operator+=(float const f) {
		for (vec3d& v : vec) {
			v.x += f;
			v.y += f;
		}
	}

	//TODO
	//bool operator==(shapeBase const& other) const{
	//	size_t const thisVecSize = sizeof(vec) / sizeof(vec[0]);

	//	if (sizeof(other.vec) / sizeof(other.vec[0]) != thisVecSize) {
	//		return false;
	//	}

	//	for (int i = 0; i < thisVecSize; ++i) {
	//		if (vec[i].x!= other.vec[i].x) return false;
	//		if (vec[i].y!= other.vec[i].y) return false;
	//		if (vec[i].z!= other.vec[i].z) return false;
	//	}

	//	return true;
	//}

	inline void translateX(float const f) { for (vec3d& v : vec) { v.x += f; } }
	inline void translateY(float const f) { for (vec3d& v : vec) { v.y += f; } } 
	inline void translateZ(float const f) { for (vec3d& v : vec) { v.z += f; } }

	inline void multByMatrix(mat4x4 const& m) { for (vec3d& v : vec) { v.multByMatrix(m); } }

	shapeBase getTriMultByMatrix(mat4x4 const& m) const {
		shapeBase reply;
		for (int i = 0; i < NumEdges; ++i) {
			reply.vec[i] = vec[i].getVecMultByMatrix(m);
		}
		return reply;
	}

	//https://math.stackexchange.com/questions/305642/how-to-find-surface-normal-of-a-triangle
	vec3d getNormal() const {
		vec3d reply;
		
		vec3d const v = vec[1] - vec[0];
		vec3d const w = vec[2] - vec[0];

		reply.x = v.y * w.z - v.z * w.y;
		reply.y = v.z * w.x - v.x * w.z;
		reply.z = v.x * w.y - v.y * w.x;

		//reply.normalize();
		return reply;
	}

	//TODO: this worked
	vec3d getNormalVectorFromCentroid() const {
		//
		//working.multByMatrix(matProj);
		//working.scaleIntoView((float)m_nScreenWidth, (float)m_nScreenHeight);
		//DrawTriangle(working, FG_WHITE);

		//if (i == 0) {
		//	vec3d centroid = working.getCentroid();
		//	vec3d extended = centroid + working.getNormal() * 15;
		//	DrawLine(centroid.x, centroid.y, extended.x, extended.y, FG_DARK_YELLOW);
		//}
		//
	}

	vec3d getCentroid() const {
		float x(0);
		float y(0);
		float z(0);

		for (int i = 0; i < NumEdges; ++i) {
			x += vec[i].x;
			y += vec[i].y;
			z += vec[i].z;
		}

		x /= NumEdges;
		y /= NumEdges;
		z /= NumEdges;

		return vec3d{x, y, z};
	}


	//TODO: figure out why these numbers work
	void scaleIntoView(float const screenWidth, float const screenHeight) {

		//TODO
		//for (int i = 0; i < NumEdges; ++i) {
		//	vec[i].scaleIntoView(screenWidth, screenHeight);
		//}

		*this += 1.0f;

		vec[0].x *= 0.5f * screenWidth;
		vec[0].y *= 0.5f * screenHeight;
		vec[1].x *= 0.5f * screenWidth;
		vec[1].y *= 0.5f * screenHeight;
		vec[2].x *= 0.5f * screenWidth;
		vec[2].y *= 0.5f * screenHeight;
	}
};