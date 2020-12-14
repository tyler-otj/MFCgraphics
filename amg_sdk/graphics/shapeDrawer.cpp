#include "ShapeDrawer.h"
#include "../util/color.h"

namespace {
	void draw(int x, int y, COLORREF* buff, int const width, int const height) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			buff[y * width + x] = colors::blue;
		}
	}
}

void ShapeDrawer::drawLine(int x1, int y1, int x2, int y2, COLORREF* buff, int const width, int const height) {
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = x1; y = y1; xe = x2;
		} else {
			x = x2; y = y2; xe = x1;
		}

		draw(x, y, buff, width, height);

		for (i = 0; x < xe; ++i) {
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			draw(x, y, buff, width, height);
		}
	} else {
		if (dy >= 0) {
			x = x1; y = y1; ye = y2;
		} else {
			x = x2; y = y2; ye = y1;
		}

		draw(x, y, buff, width, height);

		for (i = 0; y < ye; ++i) {
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			draw(x, y, buff, width, height);
		}
	}
}

void ShapeDrawer::drawTriangle(triangle const& t, COLORREF* buff, int const width, int const height) {
	drawLine((int)t.vec[0].x, (int)t.vec[0].y, (int)t.vec[1].x, (int)t.vec[1].y, buff, width, height);
	drawLine((int)t.vec[1].x, (int)t.vec[1].y, (int)t.vec[2].x, (int)t.vec[2].y, buff, width, height);
	drawLine((int)t.vec[2].x, (int)t.vec[2].y, (int)t.vec[0].x, (int)t.vec[0].y, buff, width, height);
}