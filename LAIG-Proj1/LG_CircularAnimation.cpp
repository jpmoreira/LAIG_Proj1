//
//  LG_CircularAnimation.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_CircularAnimation.h"

#define LG_CircularAnimation_Center_XML_Att_Name "center"
#define LG_CircularAnimation_Radius_XML_Att_Name "radius"
#define LG_CircularAnimation_StartAng_XML_Att_Name "startang"
#define LG_CircularAnimation_RotAng_XML_Att_Name "rotang"


LG_CircularAnimation::LG_CircularAnimation(LG_Node_Map *map,TiXmlElement *elem):LG_Animation(map,elem){
    
    double_tryToAttributeVariable(LG_CircularAnimation_Radius_XML_Att_Name, elem, radius);
    double_tryToAttributeVariable(LG_CircularAnimation_StartAng_XML_Att_Name, elem, initial_angle);
    double_tryToAttributeVariable(LG_CircularAnimation_RotAng_XML_Att_Name, elem, rotation_angle);
    point3D_tryToAttributeVariable(LG_CircularAnimation_Center_XML_Att_Name, elem, center);
    
    
    
    
}

void LG_CircularAnimation::apply(){
    
    glTranslated(center[X_], center[Y_], center[Z_]);
    glRotated(currentAngle, 0, 1, 0);
    glTranslated(radius,0,0);
    
    

}

void LG_CircularAnimation::update(unsigned long timeNow){
    
    
    if (!started){
        startTime=timeNow;
        started=true;
    }
    
    else if(timeNow-startTime<span){
    
        unsigned long timePassed=timeNow-startTime;
        
        double angularVel=rotation_angle/span;
        
        currentAngle=initial_angle+angularVel*timePassed;
    
    }


}