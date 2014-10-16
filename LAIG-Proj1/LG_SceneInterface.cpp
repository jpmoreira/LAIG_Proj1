#include "LG_SceneInterface.h"

#define _LightPanelName_ "Lights"

//LG_SceneInterface::lights_intf = new vector < int > ;

LG_SceneInterface::LG_SceneInterface()
{
	/*for (unsigned int i = GL_LIGHT0; i <= GL_LIGHT7; i++)
		lights_intf.push_back(0);*/
}


LG_SceneInterface::~LG_SceneInterface()
{
}


void LG_SceneInterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel = addPanel(_LightPanelName_, 1);
	//addCheckboxToPanel(varPanel, "Light 0", &(((LightingScene*) scene)->enable_light0), LIGHT0);
	for (unsigned int i = 0; i < lights_container->childsIDs.size(); i++)
	{
		LG_Light *light;
		auto it = lights_container->map->find(lights_container->childsIDs[i]);
		if (it != lights_container->map->end())
		{
			light = (LG_Light *)(it->second);
			
			char *tmp = new char[light->getName().length()];
			strcpy(tmp, light->getName().c_str());
			
			
			GLUI_Checkbox *checkbox;
			int *tmp_int = new int(0);
			lights_intf.push_back(tmp_int);
			checkbox= addCheckboxToPanel(varPanel, tmp, tmp_int, light->getGL_LIGHTID());
			if (light->isEnabled())
				*tmp_int = 1;
				
			
			//delete[] tmp;
		}
	}
}
void LG_SceneInterface::processGUI(GLUI_Control *ctrl)
{
	if (ctrl->user_id >= GL_LIGHT0 && ctrl->user_id <=GL_LIGHT7)
	{
		for (unsigned int i = 0; i < lights_container->childsIDs.size(); i++)
		{
			LG_Light *light;
			auto it = lights_container->map->find(lights_container->childsIDs[i]);
			if (it != lights_container->map->end())
			{
				light = (LG_Light *)(it->second);
				if (light->getGL_LIGHTID() == ctrl->user_id)
				{
					if (light->isEnabled())
						light->disable();
					else
						light->enable();
					break;
				}

			}
		}
	}

}



void LG_SceneInterface::processKeyboard(unsigned char key, int x, int y){}




void LG_SceneInterface::setLightsContainer(LG_Scene *scene)
{
	lights_container = scene->getAnf()->getLightsContainer();
}


void LG_SceneInterface::setCamerasContainer(LG_Scene *scene)
{
	cameras_container = scene->getAnf()->getCamerasContainer();
}