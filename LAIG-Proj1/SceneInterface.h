#pragma once
#include "CGFinterface.h"
#include "LG_Scene.h"


class SceneInterface :
	public CGFinterface
{
public:
	SceneInterface();

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);
	virtual void processKeyboard(unsigned char key, int x, int y);


	~SceneInterface();
};

