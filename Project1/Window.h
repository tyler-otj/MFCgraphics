#pragma once
#include "structures/shapes/shapes.h"
#include "structures/shapes/canonicalShapes.h"
#include "fps_calculator.h"
#include "Scene.h"

#include <Windows.h>

class Window{
private:
	mesh meshCube;
	Scene scene;
	float m_elapsedTime;
	fps_calculator fpsCalculator;

	void update_title_fps();

protected:
	HWND m_hwnd;
	bool m_is_run;

	constexpr static int const m_width = 1024;
	constexpr static int const m_height = 768;

public:
	Window();

	bool init();
	bool broadcast();
	bool release();
	bool isRun() const;

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();
};