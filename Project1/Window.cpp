#include "Window.h"
#include <stdexcept>
#include <algorithm>

Window::Window() {}
Window::~Window() {}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		case WM_CREATE:
			{
				// Event fired when the window is created
				// collected here..
				Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
				// .. and then stored for later lookup
				SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)window);
				window->onCreate();
				break;
			}

		case WM_DESTROY:
			{
				// Event fired when the window is destroyed
				Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
				window->onDestroy();
				::PostQuitMessage(0);
				break;
			}

		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init() {
	//Setting up WNDCLASSEX object
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) {
		return false;
	}

	//Creation of the window
	m_hwnd = ::CreateWindowEx
	(
		WS_EX_OVERLAPPEDWINDOW, 
		"MyWindowClass", 
		"Test Application",
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, //initial x starting pos
		CW_USEDEFAULT, //initial y starting pos
		m_width, 
		m_height,
		NULL, //hwnd of parent
		NULL, //hwnd to menu
		NULL, //hwnd to associated module instance?
		this
	);

	if (!m_hwnd)
		return false;

	//show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_run = true;




	//
	m_elapsedTime = 0.0f;
	meshCube = canonicalShapes::getCanonicalCube();

	//Projection Matrix
	float const fNear = 0.1f;
	float const fFar = 1000.0f;
	float const fFov = 90.0f;
	float const fAspectRatio = (float)m_height / (float)m_width;
	float const fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj = mat4x4::projection(fAspectRatio, fFovRad, fFar, fNear);

	lightDirection = { 0.0f, 0.0f, -1.0f };
	lightDirection.normalize();
	//




	return true;
}

bool Window::broadcast() {
	MSG msg;

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1); //TODO: why is this needed?

	return true;
}

bool Window::release() {
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::isRun() const{
	return m_is_run;
}

void Window::onCreate() {}

namespace {
	//bgr
	static const COLORREF blue = RGB(255, 0, 0);
	static const COLORREF green = RGB(0, 255, 0);
	static const COLORREF red = RGB(0, 0, 255);
	static const COLORREF colors[3] = { blue, green, red };
}

namespace {
	void draw(int x, int y, COLORREF* buff, int const width, int const height) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			buff[y * width + x] = blue;
		}
	}

	void drawLine(int x1, int y1, int x2, int y2, COLORREF* buff, int const width, int const height) {
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

	void drawTriangle(triangle const& t, COLORREF* buff, int const width, int const height) {
		drawLine((int)t.vec[0].x, (int)t.vec[0].y, (int)t.vec[1].x, (int)t.vec[1].y, buff, width, height);
		drawLine((int)t.vec[1].x, (int)t.vec[1].y, (int)t.vec[2].x, (int)t.vec[2].y, buff, width, height);
		drawLine((int)t.vec[2].x, (int)t.vec[2].y, (int)t.vec[0].x, (int)t.vec[0].y, buff, width, height);
	}
}

void Window::onUpdate() {
	HDC const hdc = GetDC(m_hwnd);
	if (hdc == NULL) {
		throw std::runtime_error("Could not recieve device context");
	}

	//TODO: this should be able to be created on the stack?
	COLORREF* buff = reinterpret_cast<COLORREF*>(calloc(m_width * m_height, sizeof(COLORREF)));


	//
	mat4x4 const rotZ = mat4x4::rotateZ(fTheta * 0.5f);
	mat4x4 const rotX = mat4x4::rotateX(fTheta);

	++m_elapsedTime;
	float fTheta = 0.02f * m_elapsedTime;

	std::vector<triangle> triToRaster;

	for (int i = meshCube.tris.size() - 1; i >= 0; --i) {
		/*triangle working = meshCube.tris.at(i).getTriMultByMatrix(rotX);*/
		triangle working = meshCube.tris.at(i).getTriMultByMatrix(mat4x4::rotateY(fTheta));
		working.multByMatrix(mat4x4::rotateX(0.5));

		working.translateZ(3.0f);

		vec3d normal = working.getNormal();

		//if camera ray is aligned with normal, it is visible (only draw visible faces)
		if (normal.dotProduct(working.vec[0] - camera) < 0.0f) {
			float const dotProduct = normal.dotProduct(lightDirection);
			//working.color = color::getColor(dotProduct).Attributes;

			working.multByMatrix(matProj);
			working.scaleIntoView((float)m_width, (float)m_height);
			triToRaster.push_back(working);
		}
	}

	//sort on avg z
	sort(triToRaster.begin(), triToRaster.end(), [](triangle const& t1, triangle const& t2) {
		float const z1 = (t1.vec[0].z + t1.vec[1].z + t1.vec[2].z) / 3.0f;
		float const z2 = (t2.vec[0].z + t2.vec[1].z + t2.vec[2].z) / 3.0f;
		return z1 > z2;
	});

	for (triangle t : triToRaster) {
		drawTriangle(t, buff, m_width, m_height);
	}
	//





	HBITMAP map = CreateBitmap(m_width, m_height,
		1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
		8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
		buff);

	HDC src = CreateCompatibleDC(hdc); 	// Temp HDC to copy picture
	SelectObject(src, map); // Inserting picture into our temp HDC
	BitBlt(hdc, 0, 0, m_width, m_height, src, 0, 0, SRCCOPY);

	DeleteObject(map);
	DeleteDC(src); // Deleting temp HDC
	free(buff);
}

void Window::onDestroy() {
	m_is_run = false;
}