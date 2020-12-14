#include "gameWindow.h"
#include "../amg_sdk/graphics/shapeDrawer.h"

#include <algorithm>

gameWindow::gameWindow() {
	//Projection Matrix
	float const fNear = 0.1f;
	float const fFar = 1000.0f;
	float const fFov = 90.0f;
	float const fAspectRatio = (float)m_height / (float)m_width;
	float const fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	mat4x4 matProj = mat4x4::projection(fAspectRatio, fFovRad, fFar, fNear);

	vec3d lightDirection = { 0.0f, 0.0f, -1.0f };
	lightDirection.normalize();

	m_scene = scene(matProj, lightDirection, vec3d());
	m_scene.add_mesh("C:\\Users\\tyler\\Desktop\\objFiles\\in progress\\joined ship.obj");
}

void gameWindow::draw() {
	float fTheta = 0.03f * m_elapsedTime;
	std::vector<triangle> triToRaster;

	for (mesh const& m : m_scene.get_meshes()) {
		for (int i = m.tris.size() - 1; i >= 0; --i) {
			triangle working = m.tris.at(i).getTriMultByMatrix(mat4x4::rotateY(fTheta));

			working.translateZ(63.0f);

			vec3d normal = working.getNormal();

			//if camera ray is aligned with normal, it is visible (only draw visible faces)
			//if (normal.dotProduct(working.vec[0] - camera) < 0.0f) {
			if (true) {
				float const dotProduct = normal.dotProduct(m_scene.lightDirection);

				working.multByMatrix(m_scene.matProj);
				working.scaleIntoView((float)m_width, (float)m_height);
				triToRaster.push_back(working);
			}
		}
	}

	//sort on avg z
	sort(triToRaster.begin(), triToRaster.end(), [](triangle const& t1, triangle const& t2) {
		float const z1 = (t1.vec[0].z + t1.vec[1].z + t1.vec[2].z) / 3.0f;
		float const z2 = (t2.vec[0].z + t2.vec[1].z + t2.vec[2].z) / 3.0f;
		return z1 > z2;
	});

	for (triangle const& t : triToRaster) {
		ShapeDrawer::drawTriangle(t, buff.get(), m_width, m_height);
	}

	parent::draw();
}

