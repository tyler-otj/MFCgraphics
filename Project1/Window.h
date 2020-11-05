#pragma once
#include "structures/shapes/shapes.h"
#include "structures/shapes/canonicalShapes.h"

#include <chrono>
#include <Windows.h>

class Window{
private:
	mesh meshCube;
	mat4x4 matProj;
	float fTheta;
	vec3d camera;
	vec3d lightDirection;
	float m_elapsedTime;

	//fps claculations
	std::chrono::time_point<std::chrono::system_clock> tp1;
	std::chrono::time_point<std::chrono::system_clock> tp2;

	void set_title_with_fps();
protected:
	HWND m_hwnd;
	bool m_is_run;

	static int const m_width = 1024;
	static int const m_height = 768;

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