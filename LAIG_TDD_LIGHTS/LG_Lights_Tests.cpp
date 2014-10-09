#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#endif

#define DOUBLE_MARGIN 0.0001


#include "LG_Lights_Container.h"

#include <CGFapplication.h>

#include <iostream>
#include <fstream>


TEST_CASE("Test loading Graph Node from XML"){


#ifdef __WIN32
	TiXmlDocument *doc = new TiXmlDocument("TestLights.xml");
#else
    TiXmlDocument *doc = new TiXmlDocument("testFiles/TestLights.xml");
#endif
	REQUIRE(doc->LoadFile());
	LG_Node_Map *map = new LG_Node_Map();

	TiXmlElement *firstElement = doc->FirstChildElement();




	SECTION("Testing perfectly well formed Appearance"){

		LG_Lights_Container *lights_container = NULL;
		int nr_childs;
		try{
			lights_container = new LG_Lights_Container(map, firstElement);
			nr_childs =(int) lights_container->childsIDs.size();
		}
		catch (LG_Parse_Exception e){
			FAIL("Cannot instantiate LG_Lights_Cointainer");
		}



		try {
			REQUIRE(str_eq(lights_container->getIdentifier().c_str(), LG_LIGHTS_CONTAINER_ID));
			REQUIRE(nr_childs == 2);

	
			

			LG_Light_Spot *spot = NULL;
			LG_Light_Omni *omni = NULL;

			string spot_id = "spot1";
			string omni_id = "omni1";

			auto it = map->find(spot_id);
			
			//spot light tests
			spot = (LG_Light_Spot *)(it->second);
			REQUIRE(it != map->end());
			REQUIRE((spot->getEnabled()) == false);
			REQUIRE((spot->getMarker()) == true);
			REQUIRE(spot->getPos()[0] == 5);
			REQUIRE(spot->getPos()[1] == 5);
			REQUIRE(spot->getPos()[2] == 5);
			REQUIRE(spot->getTarget()[0] == 10);
			REQUIRE(spot->getTarget()[1] == 11);
			REQUIRE(spot->getTarget()[2] == 12);
			REQUIRE(abs(spot->getAngle() - 10.0) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getExponent() - 0.5) <= DOUBLE_MARGIN);

			//ambient component
			REQUIRE(abs(spot->getComponents()[0][0] - 0.8) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[0][1] - 0.7) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[0][2] - 0.4) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[0][3] - 12) <= DOUBLE_MARGIN);
		
			//diffuse component
			REQUIRE(abs(spot->getComponents()[1][0] - 0.4) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[1][1] - 0.7) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[1][2] - 0.8) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[1][3] - 15) <= DOUBLE_MARGIN);
			
			//specular component
			REQUIRE(abs(spot->getComponents()[2][0] - 0.4) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[2][1] - 0.7) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[2][2] - 0.8) <= DOUBLE_MARGIN);
			REQUIRE(abs(spot->getComponents()[2][3] - 20) <= DOUBLE_MARGIN);

			
			
			
			
			//omni light tests
			it = map->find(omni_id);
			omni = (LG_Light_Omni *)it->second;
			REQUIRE(it != map->end());
			REQUIRE(omni->getEnabled() == true);
			REQUIRE(omni->getMarker() == false);
			REQUIRE(omni->getPos()[0] == 5);
			REQUIRE(omni->getPos()[1] == 5);
			REQUIRE(omni->getPos()[2] == 5);

			//ambient component
			REQUIRE(abs(omni->getComponents()[0][0] - 0.4) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[0][1] - 0.7) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[0][2] - 0.8) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[0][3] - 1) <= DOUBLE_MARGIN);

			//diffuse component
			REQUIRE(abs(omni->getComponents()[1][0] - 0.4) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[1][1] - 0.7) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[1][2] - 0.8) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[1][3] - 1) <= DOUBLE_MARGIN);

			//specular component
			REQUIRE(abs(omni->getComponents()[2][0] - 0.4) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[2][1] - 0.7) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[2][2] - 0.8) <= DOUBLE_MARGIN);
			REQUIRE(abs(omni->getComponents()[2][3] - 1) <= DOUBLE_MARGIN);




		}
		catch (LG_Parse_Exception *ex) {
			FAIL("Thrown exception while parsing perfectly good appearance");
		}


	}


}
