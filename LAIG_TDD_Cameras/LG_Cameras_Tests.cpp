#ifndef LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#endif

#define DOUBLE_MARGIN 0.0001

//#include <CGFapplication.h>


#include "LG_Cameras_Container.h"

TEST_CASE("Test loading Graph Node from XML"){


	TiXmlDocument *doc = new TiXmlDocument("testCameras.xml");

	REQUIRE(doc->LoadFile());
	LG_Node_Map *map = new LG_Node_Map();
	TiXmlElement *firstElement; 


	SECTION("Testing perfectly well formed Cameras"){

		//try {

		//	REQUIRE(true == true);
		//	//REQUIRE(str_eq(lights_container->getIdentifier().c_str(), LG_LIGHTS_CONTAINER_ID));



		//}
		//catch (LG_Parse_Exception *ex) {
		//	FAIL("Thrown exception while parsing perfectly good appearance");
		//}



			firstElement = doc->FirstChildElement(LG_CAMERAS_XML_TAG_NAME);
			REQUIRE(firstElement);
	




	}


}