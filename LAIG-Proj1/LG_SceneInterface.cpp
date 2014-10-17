#include "LG_SceneInterface.h"

//LG_SceneInterface::lights_intf = new vector < int > ;

LG_SceneInterface::LG_SceneInterface()
{
    /*for (unsigned int i = GL_LIGHT0; i <= GL_LIGHT7; i++)
     lights_intf.push_back(0);*/
    selected_cam = 0;
}


LG_SceneInterface::~LG_SceneInterface()
{
}


void LG_SceneInterface::initGUI()
{
    
    
    //LIGHTS
    //---------------------------------------------------------------------
    GLUI_Panel *lightsPanel = addPanel("Lights", 1);
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
            int *tmp_int = new int(UNCHECKED);
            lights_intf.push_back(tmp_int);
            checkbox = addCheckboxToPanel(lightsPanel, tmp, tmp_int, light->getGL_LIGHTID());
            if (light->isEnabled())
                *tmp_int = CHECKED;
            
            if (i == LIGHTS_COLUMN) //maxcams is 7
                addColumnToPanel(lightsPanel);
            //delete[] tmp;
        }
    }
    
    
    //CAMERAS
    //--------------------------------------------------------------------------
    glui_window->add_column(false);
    GLUI_Panel *cameras_pan = addPanel("Cameras", 1);
    GLUI_Listbox *cameras_list;
	cameras_list = addListboxToPanel(cameras_pan, "Camera", &selected_cam, CAMERA_LIST);
    
    
    LG_Camera *camera;
    string current_cam_id = cameras_container->getCurrentCamera()->getIdentifier();
    for (unsigned int i = 0; i < cameras_container->childsIDs.size(); i++)
    {
        auto it = cameras_container->map->find(cameras_container->childsIDs[i]);
        if (it != cameras_container->map->end())
        {
            camera = (LG_Camera *)(it->second);
            char *tmp = new char[camera->getIdentifier().length()];
            strcpy(tmp, camera->getIdentifier().c_str());
            cameras_list->add_item(i, tmp);
            
            if (str_eq(tmp, current_cam_id.c_str()))
                selected_cam = i;
        }
    }
    cameras_list->set_int_val(selected_cam);
    cameras_container->setCurrentCamera(selected_cam);
    CGFapplication::activeApp->forceRefresh();
    
	//Drawing
	//--------------------------------------------------------------------------

	addSeparator();

	GLUI_Panel *drawing_pan = addPanel("Drawing", 1);
	GLUI_Listbox *drawing_list;
	drawing_list = addListboxToPanel(drawing_pan, "Mode", &selected_drawing, DRAWING_LIST);
	drawing_list->add_item(LG_Drawing_Fill, DRAWING_FILL_STR);
	drawing_list->add_item(LG_Drawing_Line, DRAWING_LINE_STR);
	drawing_list->add_item(LG_Drawing_Point, DRAWING_POINT_STR);
	selected_drawing = drawing->getMode();
    
}
void LG_SceneInterface::processGUI(GLUI_Control *ctrl)
{
    if (ctrl->user_id >= GL_LIGHT0 && ctrl->user_id <= GL_LIGHT7)
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
	else if (ctrl->user_id == CAMERA_LIST)
    {
        cameras_container->setCurrentCamera(selected_cam);
    }
	else if (ctrl->user_id == DRAWING_LIST)
	{
		drawing->setMode((LG_Drawing_Mode)selected_drawing);
		//drawing->draw();
        
	}
    
	/*
	if (mode == LG_Drawing_Line) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (mode == LG_Drawing_Point) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (mode == LG_Drawing_Fill)
	*/
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

void LG_SceneInterface::setDrawing(LG_Scene *scene)
{
	drawing = scene->getAnf()->getDrawing();
}