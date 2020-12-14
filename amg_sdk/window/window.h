#pragma once
#include "../structures/shapes/shapes.h"
#include "../structures/shapes/canonicalShapes.h"
#include "../util/fps_calculator.h"
#include "../graphics/scene.h"

#include <Windows.h>
#include <memory>

class window{
private:
	constexpr static int const m_width = 1024;
	constexpr static int const m_height = 768;

	HDC hdc;
	std::unique_ptr<COLORREF[]> buff;
	mesh meshCube;
	scene m_scene;

	float m_elapsedTime;
	fps_calculator fpsCalculator;

	void update_title_fps();

protected:
	HWND m_hwnd;
	bool m_is_run;

	//TODO: find a better way to do this! child classes MUST call prepareToDraw as its first line, then draw as its last line in its update function!
	virtual void prepareToDraw();
	virtual void draw();

public:
	window();

	bool init();
	bool broadcast();
	bool release();
	bool isRun() const;

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~window();
};