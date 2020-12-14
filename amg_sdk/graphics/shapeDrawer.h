#pragma once
#include <windows.h>
#include "../structures/shapes/shapes.h"

class ShapeDrawer{
public:
	static void drawLine(int x1, int y1, int x2, int y2, COLORREF* buff, int const width, int const height);
	static void drawTriangle(triangle const& t, COLORREF* buff, int const width, int const height);
};