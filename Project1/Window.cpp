#include "Window.h"
#include "color.h"
#include "ShapeDrawer.h"
#include <stdexcept>
#include <algorithm>
#include <string>

namespace {
	static const std::string title("Cool Gfx Bro");
}

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
		&title[0],
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
	//meshCube = canonicalShapes::getCanonicalCube();

	if (!meshCube.load_object_file("C:\\Users\\tyler\\Desktop\\objFiles\\in progress\\joined ship.obj")) {
		throw std::runtime_error("Unable to load object file");
	}

	//Projection Matrix
	float const fNear = 0.1f;
	float const fFar = 1000.0f;
	float const fFov = 90.0f;
	float const fAspectRatio = (float)m_height / (float)m_width;
	float const fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj = mat4x4::projection(fAspectRatio, fFovRad, fFar, fNear);

	lightDirection = { 0.0f, 0.0f, -1.0f };
	lightDirection.normalize();

	return true;
}

bool Window::broadcast() {
	MSG msg;

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

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

void Window::update_title_fps() {
	std::ostringstream ss;
	ss << title << ' ' << fpsCalculator.get_fps();

	if (!SetWindowTextA(m_hwnd, ss.str().c_str())) {
		throw std::runtime_error("Unable to set window title.");
	}
}

void Window::onUpdate() {
	update_title_fps();

	HDC const hdc = GetDC(m_hwnd);
	if (hdc == NULL) {
		throw std::runtime_error("Could not recieve device context");
	}

	//TODO: this should be able to be created on the stack?
	COLORREF* buff = reinterpret_cast<COLORREF*>(calloc(m_width * m_height, sizeof(COLORREF)));
	//
	++m_elapsedTime;
	float fTheta = 0.03f * m_elapsedTime;

	std::vector<triangle> triToRaster;

	for (int i = meshCube.tris.size() - 1; i >= 0; --i) {
		/*triangle working = meshCube.tris.at(i).getTriMultByMatrix(rotX);*/
		triangle working = meshCube.tris.at(i).getTriMultByMatrix(mat4x4::rotateY(fTheta));
		//triangle working = meshCube.tris.at(i).getTriMultByMatrix(mat4x4::rotateY(-0.7));
		//working.multByMatrix(mat4x4::rotateX(0.7));

		working.translateZ(63.0f);

		vec3d normal = working.getNormal();

		//if camera ray is aligned with normal, it is visible (only draw visible faces)
		/*if (normal.dotProduct(working.vec[0] - camera) < 0.0f) {*/
		if (true) {
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
		ShapeDrawer::drawTriangle(t, buff, m_width, m_height);
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