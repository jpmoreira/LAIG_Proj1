#pragma once
#include "CGFinterface.h"
#include "LG_Scene.h"

#define CHECKED 1
#define UNCHECKED 0
#define LIGHTS_COLUMN 3
#define LIGHTS_PANEL 1
#define CAMERA_LIST 2
#define DRAWING_LIST 3

#define DRAWING_FILL_STR "Fill"
#define DRAWING_LINE_STR "Line"
#define DRAWING_POINT_STR "Point"



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
	void setDrawing(LG_Scene *scene);
	void setWind_var(int *flag_windvar);
	//float afloat;


	~LG_SceneInterface();

private:
	LG_Lights_Container *lights_container;
	LG_Cameras_Container *cameras_container;
	LG_Drawing *drawing;
	vector<int *> lights_intf;
	
	
	
	int selected_cam;
	int selected_drawing;
	int *wind_var;


};

