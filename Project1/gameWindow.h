#pragma once
#include "../amg_sdk/window/window.h"

class gameWindow : public window {
private:
	typedef window parent;

	mesh meshCube;
	scene m_scene;

	virtual void prepareToDraw() override;
	virtual void draw() override;
	virtual void onUpdate() override;

public:
	gameWindow();
};