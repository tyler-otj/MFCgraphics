#pragma once
#include "../amg_sdk/window/window.h"
#include "../amg_sdk/structures/shapes/shapes.h"
#include "../amg_sdk/graphics/scene.h"

class gameWindow : public window {
private:
	typedef window parent;
	scene m_scene;

	//MUST call parent::draw as last line
	virtual void draw() override;

public:
	gameWindow();
};