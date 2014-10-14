#pragma once
#include "LG_Parsable_Node.h"
#include "LG_Camera_Ortho.h"
#include "LG_Camera_Perspective.h"



#define LG_CAMERAS_TAG_ID "lg_cameras"
#define LG_CAMERAS_XML_TAG_NAME "cameras"
#define LG_CAMERAS_ATT_INITIAL "initial"


class LG_Cameras_Container :
	public LG_Parsable_Node
{
public:
	LG_Cameras_Container( TiXmlElement *element);
	~LG_Cameras_Container();

	/**
		returns the id of the initial camera
	*/
	LG_Camera * getCurrentCamera();

	/**
		Checks if this is the correct tag
	*/
	void verifyElementName(TiXmlElement *element);

	/**
		Checks if initial attribute is set. Calls setOrthoCams() and setPerspectiveCams()
		Throws exception if initial cam was not set.
	*/
	void verifyAttributesAndValues(TiXmlElement *element);

	/**
		Sets the Ortho Cams.
		@return true if initial camera is found and set, false otherwise
	*/
	bool setOrthoCams(TiXmlElement *element,string & initialID);

	/**
	Sets the Perspective Cams.
	@return true if initial camera is found and set, false otherwise
	*/
	bool setPerspectiveCams(TiXmlElement *element,string & initialID);



private:
	LG_Camera * current;
};

