#include "SceneInterface.h"


SceneInterface::SceneInterface()
{
	GLUI_Panel *varPanel = addPanel("Lights", 1);

}


SceneInterface::~SceneInterface()
{
}


void SceneInterface::initGUI(){}
void SceneInterface::processGUI(GLUI_Control *ctrl){}
void SceneInterface::processKeyboard(unsigned char key, int x, int y){}