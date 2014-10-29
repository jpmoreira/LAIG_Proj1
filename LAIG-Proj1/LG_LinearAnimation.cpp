//
//  LG_LinearAnimation.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_LinearAnimation.h"


#define LG_ControlPoint_XML_Tag_Name "controlpoint"
#define LG_ControlPoint_XX_XML_Att_Name "xx"
#define LG_ControlPoint_YY_XML_Att_Name "yy"
#define LG_ControlPoint_ZZ_XML_Att_Name "zz"

#pragma mark - Constructors

LG_LinearAnimation::LG_LinearAnimation(LG_Node_Map *map,string identifier,vector<double *> points,double duration):LG_Animation(map,identifier,duration),controlPoints(points){
    
    
    
    

    
}

LG_LinearAnimation::LG_LinearAnimation(LG_Node_Map *map,TiXmlElement *element):LG_Animation(map,element),controlPoints(vector<double *>()){


    handleControlPoints(element);
    
    
    
}


#pragma mark - Animation Application

void LG_LinearAnimation::apply(long int timeElapsed){


}


#pragma mark - Helper Methods

void LG_LinearAnimation::handleControlPoints(TiXmlElement *animationElement){


    TiXmlElement *possibleControlPoint=animationElement->FirstChildElement();
    
    
    while (possibleControlPoint) {
        
        double *point=new double[3];
        
        
        evalElemName(LG_ControlPoint_XML_Tag_Name, possibleControlPoint->Value());
        
        
        double_tryToAttributeVariable(LG_ControlPoint_XX_XML_Att_Name, possibleControlPoint, point[0]);
        double_tryToAttributeVariable(LG_ControlPoint_YY_XML_Att_Name, possibleControlPoint, point[1]);
        double_tryToAttributeVariable(LG_ControlPoint_ZZ_XML_Att_Name, possibleControlPoint, point[2]);
        
        controlPoints.push_back(point);
    
        
        
        possibleControlPoint=possibleControlPoint->NextSiblingElement();
    }
    
    if (controlPoints.size()<2) {
        throw new LG_Parse_Exception_Missing_Element(LG_ControlPoint_XML_Tag_Name);
    }
    

}

