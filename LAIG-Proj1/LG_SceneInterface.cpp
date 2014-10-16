#include "LG_SceneInterface.h"

int *k;
LG_SceneInterface::LG_SceneInterface()
{
	lights_event = 0;
	cameras_event = 0;
}


LG_SceneInterface::~LG_SceneInterface()
{
}


void LG_SceneInterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel = addPanel("Lights", 1);
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
			addCheckboxToPanel(varPanel, tmp, &lights_event, light->getGL_LIGHTID());
			//delete[] tmp;
		}
	}
}
void LG_SceneInterface::processGUI(GLUI_Control *ctrl)
{
	if (lights_event)
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

					lights_event = 0;
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