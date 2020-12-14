#pragma once
#include "../util/fps_calculator.h"

#include <Windows.h>
#include <memory>

class window{
private:
	HDC hdc;
	fps_calculator fpsCalculator;
	void update_title_fps();

protected:
	std::unique_ptr<COLORREF[]> buff;
	float m_elapsedTime;
	constexpr static int const m_width = 1024;
	constexpr static int const m_height = 768;
	HWND m_hwnd;
	bool m_is_run;

	//children MUST CALL THIS as last line
	virtual void draw();

public:
	window();

	bool broadcast();
	bool release();
	bool isRun() const;

	//EVENTS
	virtual void onUpdate();
	virtual void onDestroy();
};