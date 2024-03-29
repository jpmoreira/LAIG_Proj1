#pragma once


//class LG_Lighting : public LG_Parsable_Node{

#include "LG_Camera.h"




#define LG_Camera_Perspective_XML_ATT_ANGLE "angle"
#define LG_Camera_Perspective_XML_ATT_POS "pos"
#define LG_Camera_Perspective_XML_ATT_TARGET "target"


class LG_Camera_Perspective : public LG_Camera
{
public:
    
    bool animating;
	LG_Camera_Perspective(LG_Node_Map *map, TiXmlElement *element);
	~LG_Camera_Perspective();

	void verifyElementName(TiXmlElement *element);
	void verifyAttributesAndValues(TiXmlElement* element);

	double getAngle();
	const LG_Point3D *getPos();
	const LG_Point3D *getTarget();
    
    void updateProjectionMatrix(int width, int height);
    
    
    void applyView();
    
    void update(unsigned long time);
    
    /*
    bool moveTo(int axis, float value, float increment);
    
    
    bool translate(int axis, float value);
     
     */
private:
	double angle;
    double distance;
    double initialAngle;
    
    unsigned long animationStart;
    LG_Node * owner;
    
	LG_Point3D pos, target,currentPos;
};

