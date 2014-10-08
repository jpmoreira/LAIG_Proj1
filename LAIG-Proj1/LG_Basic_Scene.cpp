#include "LG_Basic_Scene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include <math.h>
#include "LG_Appearance.h"

float pi = acos(-1.0);
float deg2rad=pi/180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4


// Positions for two lights
float light0_pos[4] = {3.25, 8.0, 3.25, 1.0};
float light1_pos[4] = {9.75, 8.0, 3.25, 1.0};

float light2_pos[4] = {3.25, 8.0, 9.75, 1.0};
float light3_pos[4] = {9.75, 8.0, 9.75, 1.0};

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4]= {0,0,0,1};

// number of divisions
#define BOARD_A_DIVISIONS 30
#define BOARD_B_DIVISIONS 100

// Coefficients for material A
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.6, 0.6, 0.6};
float specA[3] = {0, 0.8, 0.8};
float shininessA = 120.f;

// Coefficients for material B
float ambB[3] = {0.2, 0.2, 0.2};
float difB[3] = {0.6, 0.6, 0.6};
float specB[3] = {0.8, 0.8, 0.8};
float shininessB = 40.f;

// Coefficients for material floor
float amb_wall[3] = {0.135, 0.223, 0.1575};
float dif_wall[3] = {0.54, 0.89, 0.63};
float spec_wall[3] = {0.316, 0.316, 0.316};
float shininess_wall = 0.1;

// Coefficients for material wall
float amb_floor[3] = {0.02, 0.02, 0.02};
float dif_floor[3] = {0.65, 0.59, 0.48};
float spec_floor[3] = {0.26, 0.236, 0.192};
float shininess_floor = 0.15;


float ambientNull[4]={0,0,0,1};
float yellow[4]={1,1,0,1};





void LG_Basic_Scene::init()
{

    
    
    TiXmlDocument *doc=new TiXmlDocument("./testFiles/TestDraw1.xml");
    
    
    bool b=doc->LoadFile();
    
    LG_Node_Map *appMap=new LG_Node_Map();
    string identifier="uniqueExistingApp";

    
    graph=new LG_Graph(appMap,doc->FirstChildElement());
    
    

	
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);


	// Declares and enables two lights, with null ambient component

	//light0 = new CGFlight(GL_LIGHT0, light0_pos);
    light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambientNull);
	//light0->setSpecular(yellow);

	

	//light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);

	
	light1->setKc(1);
	light1->setKl(0);
	light1->setKq(0);


	//light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2 = new CGFlight(GL_LIGHT2, light2_pos);;
	light2->setAmbient(ambientNull);

	

	light2->setKc(1);
	light2->setKl(0);
	light2->setKq(0);


	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setAmbient(ambientNull);


	

	light3->setKc(0);
	light3->setKl(0);
	light3->setKq(0.2);

	// Uncomment below to enable normalization of lighting normal vectors
	glEnable (GL_NORMALIZE);

	setUpdatePeriod(100);    
}

void LG_Basic_Scene::display()
{

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

    light0->enable();
	light0->draw();
	light1->draw();
	light2->draw();
	light3->draw();

	// Draw axis
	axis.draw();
    
    graph->draw();
	//  
	//// ---- END Background, camera and axis setup

	glutSwapBuffers();


}

LG_Basic_Scene::~LG_Basic_Scene() 
{
	delete(light0);
	delete(light1);

}


