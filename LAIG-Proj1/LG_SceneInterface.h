#pragma once
#include "CGFinterface.h"
#include "LG_Scene.h"


class LG_SceneInterface :
	public CGFinterface
{
public:
	LG_SceneInterface();

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);
	virtual void processKeyboard(unsigned char key, int x, int y);
	void setLightsContainer(LG_Scene *scene);
	void setCamerasContainer(LG_Scene *scene);


	~LG_SceneInterface();

private:
	LG_Lights_Container *lights_container;
	LG_Node_Map *lights_map;
	LG_Cameras_Container *cameras_container;
	LG_Node_Map *cameras_map;
	int lights_event;
	int cameras_event;
};

