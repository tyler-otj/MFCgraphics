#pragma once
#include "../amg_sdk/window/window.h"
#include "../amg_sdk/structures/shapes/shapes.h"
#include "../amg_sdk/graphics/scene.h"

class gameWindow : public window {
private:
	typedef window parent;

	mesh meshCube;
	scene m_scene;

	virtual void draw() override;

public:
	gameWindow();
};