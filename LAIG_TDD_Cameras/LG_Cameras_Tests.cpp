#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#endif


#define private public
#define protected public

#define DOUBLE_MARGIN 0.0001

#include <CGFapplication.h>


#include "LG_Cameras_Container.h"

TEST_CASE("Test loading Graph Node from XML"){


#ifdef __WIN32
	TiXmlDocument *doc = new TiXmlDocument("testCameras.xml");
#else
    TiXmlDocument *doc = new TiXmlDocument("testFiles/testCameras.xml");

#endif
	REQUIRE(doc->LoadFile());


	LG_Node_Map *map = new LG_Node_Map();
	TiXmlElement *firstElement; 
	
	LG_Cameras_Container *cameras_container = NULL;
	LG_Camera_Ortho *camera_ortho = NULL;
	LG_Camera_Perspective *camera_perspective = NULL;

	//identifiers of the elements
	string persp_id("perspective1");
	string ortho_id("ortho1");

	double *some_lg_P3D;



	SECTION("Testing Cameras_Container"){

			firstElement = doc->FirstChildElement(LG_CAMERAS_XML_TAG_NAME);
			REQUIRE(firstElement);
			
			cameras_container = new LG_Cameras_Container(map, firstElement);
			
			//container tests
			REQUIRE(cameras_container);	//object was set
        LG_Camera *initial_camera=cameras_container->getInitial();
			REQUIRE(str_eq(initial_camera->identifier.c_str(), persp_id.c_str()));	//the initial cam was set to map
			REQUIRE(cameras_container->getNrChildren() == 2);		//nr of cameras declared inside .xml


			/*
			
			
			SECTION("Testing ortho1 camera")
			********************************************************************************
			
			
			*/
			auto it = map->find(ortho_id);
			camera_ortho = (LG_Camera_Ortho *)it->second;

			REQUIRE(camera_ortho);
			REQUIRE(abs(camera_ortho->getNear() - 0.5) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_ortho->getFar() - 1) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_ortho->getLeft() - 2) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_ortho->getRight() - 2.5) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_ortho->getBottom() - 20) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_ortho->getTop() - 15) <= DOUBLE_MARGIN);

			REQUIRE(camera_ortho->getDirection() == LG_AXIS_Z);



			/*


			SECTION("Testing perspective1 camera")
			********************************************************************************


			*/


			it = map->find(persp_id);
			camera_perspective = (LG_Camera_Perspective *)it->second;

			REQUIRE(camera_perspective);
			REQUIRE(abs(camera_perspective->getNear() - 5.5) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_perspective->getFar() - 20) <= DOUBLE_MARGIN);
			REQUIRE(abs(camera_perspective->getAngle() - 30) <= DOUBLE_MARGIN);

			some_lg_P3D = (double *)camera_perspective->getPos();
			REQUIRE(abs(some_lg_P3D[0] - 1.5) <= DOUBLE_MARGIN);
			REQUIRE(abs(some_lg_P3D[1] - 2) <= DOUBLE_MARGIN);
			REQUIRE(abs(some_lg_P3D[2] - 2.5) <= DOUBLE_MARGIN);

			some_lg_P3D = (double *)camera_perspective->getTarget();
			REQUIRE(abs(some_lg_P3D[0] - 10) <= DOUBLE_MARGIN);
			REQUIRE(abs(some_lg_P3D[1] - 10) <= DOUBLE_MARGIN);
			REQUIRE(abs(some_lg_P3D[2] - 10) <= DOUBLE_MARGIN);

	}
	
	
			
}