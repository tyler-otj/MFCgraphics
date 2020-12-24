#pragma once
#include "../util/fps_calculator.h"

#include <Windows.h>
#include <memory>

namespace presses {
	enum pressed {
		UP = 1,
		DOWN = 1 << 1,
		LEFT = 1 << 2,
		RIGHT = 1 << 3
	};
}
using presses::pressed;

namespace releases {
	enum released {
		UP = 1 << 4,
		DOWN = 1 << 5,
		LEFT = 1 << 6,
		RIGHT = 1 << 7
	};
}
using releases::released;

class window{
private:
	HDC hdc;
	fps_calculator fpsCalculator;
	void update_title_fps();
	void assign_key(LRESULT result);

protected:
	std::unique_ptr<COLORREF[]> buff;
	float m_elapsedTime;
	constexpr static int const m_width = 1024;
	constexpr static int const m_height = 768;
	HWND m_hwnd;
	bool m_is_run;
	short keysPressed;

	//children MUST CALL THIS as last line if overridden
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

void show_ok_dialog(std::string const& message);