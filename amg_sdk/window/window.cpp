#include "window.h"

#include <sstream>
#include <stdexcept>
#include <string>

namespace {
	static const std::string title("Cool Gfx Bro");

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		switch (msg) {
		case WM_CREATE:
		{
			// Event fired when the window is created collected here..
			window* w = (window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			// .. and then stored for later lookup
			SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)w);
			break;
		}

		case WM_DESTROY:
		{
			// Event fired when the window is destroyed
			window* w = (window*)GetWindowLong(hwnd, GWL_USERDATA);
			w->onDestroy();
			::PostQuitMessage(0);
			break;
		}

		case WM_KEYDOWN:
		{
			if (wparam == VK_F1) {
				show_ok_dialog("F1 Pressed");
			}
		}

		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return NULL;
	}
}

window::window() {
	buff = std::make_unique<COLORREF[]>(m_width * m_height);

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
		throw std::runtime_error("TODO");
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

	if (!m_hwnd) {
		throw std::runtime_error("TODO");
	}

	::ShowWindow(m_hwnd, SW_SHOW);

	hdc = GetDC(m_hwnd);
	if (hdc == NULL) {
		throw std::runtime_error("Could not recieve device context");
	}

	::UpdateWindow(m_hwnd);

	m_is_run = true;
	m_elapsedTime = 0.0f;
}

bool window::broadcast() {
	MSG msg;

	buff = std::make_unique<COLORREF[]>(m_width * m_height);
	onUpdate();
	draw();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

//TODO: go back in revisions and see where this was called, remove if not needed
bool window::release() {
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool window::isRun() const{
	return m_is_run;
}

void window::update_title_fps() {
	std::ostringstream ss;
	ss << title << ' ' << fpsCalculator.get_fps();

	if (!SetWindowTextA(m_hwnd, ss.str().c_str())) {
		throw std::runtime_error("Unable to set window title.");
	}
}

void window::draw() {
	HBITMAP const map = CreateBitmap(m_width, m_height,
		1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
		8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
		buff.get());

	HDC src = CreateCompatibleDC(hdc); 	// Temp HDC to copy picture
	SelectObject(src, map); // Inserting picture into our temp HDC
	BitBlt(hdc, 0, 0, m_width, m_height, src, 0, 0, SRCCOPY);

	DeleteObject(map);
	DeleteDC(src);
}

void window::onUpdate() {
	update_title_fps();
	++m_elapsedTime;
}

void window::onDestroy() {
	m_is_run = false;
}

void show_ok_dialog(std::string const& message) {
	MessageBox(NULL, message.c_str(), "title", MB_OKCANCEL);
}