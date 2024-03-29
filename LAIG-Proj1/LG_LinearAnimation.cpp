//
//  LG_LinearAnimation.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_LinearAnimation.h"

#include "LG_AnimationState.h"


#define LG_ControlPoint_XML_Tag_Name "controlpoint"
#define LG_ControlPoint_XX_XML_Att_Name "xx"
#define LG_ControlPoint_YY_XML_Att_Name "yy"
#define LG_ControlPoint_ZZ_XML_Att_Name "zz"
#define LG_Linear_Animation_Rotation_XML_Att_Name "rotation"

#pragma mark - Constructors

LG_LinearAnimation::LG_LinearAnimation(LG_Node_Map *map,string identifier,vector<double *> points,double duration):LG_Animation(map,identifier,duration),controlPoints(points){
    
}

LG_LinearAnimation::LG_LinearAnimation(LG_Node_Map *map,TiXmlElement *element):LG_Animation(map,element),controlPoints(vector<double *>()){
    
    
    handleControlPoints(element);
    
    try{
        double_tryToAttributeVariable(LG_Linear_Animation_Rotation_XML_Att_Name, element, totalRotation);
    }
    catch (LG_Parse_Exception_Missing_Attribute *ex){
        
        totalRotation = 0;
    }
    
    
    
    
    
}


#pragma mark - Animation Application


void LG_LinearAnimation::update(unsigned long timeNow,LG_AnimationState *state){
    
    
    
    
    double timeSinceStart=state->timePassed(timeNow);
    
    
    if (totalRotation != 0.0){
        
        applyRotByAnfParam(timeSinceStart, state);
    }
    
    int currentSegment=state->getCurrentSegment();
    
    if (timeToSwitchSegment<timeSinceStart && currentSegment+2<controlPoints.size()) {//if time to switch segments has passed and we have enought control points
        
        
        
        vector<double> startDirVect=directionVectorForSegment(controlPoints[0],controlPoints[1]);
        vector<double> currentDirVect=directionVectorForSegment(controlPoints[currentSegment+1], controlPoints[currentSegment+2]);
        
        printf("Applying rotation\n");
        configureRotation(startDirVect, currentDirVect, state);
        
        if (velocity!=0) {
            timeToSwitchSegment+=distanceBetweenPoints(controlPoints[currentSegment+1], controlPoints[currentSegment+2])/velocity;
            
        }
        
        
        
        
        state->incrementCurrentSegment();//we are no longer in the same segment
        
    }
    
    
    
    configureTranslation(timeSinceStart,state);
    
    
    
    
    
    
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


double LG_LinearAnimation::distanceBetweenPoints(LG_Point3D pt1,LG_Point3D pt2){
    
    double dx=pt1[0]-pt2[0];
    double dy=pt1[1]-pt2[1];
    double dz=pt1[2]-pt2[2];
    
    
    return sqrt(dx*dx+dy*dy+dz*dz);
    
}


void LG_LinearAnimation::configureInitialParameters(LG_AnimationState *state){
    
    
    
    state->translate(controlPoints[0][0], controlPoints[0][1], controlPoints[0][2]);
    
    
    controlPointHitTime=vector<double>(controlPoints.size());
    controlPointHitTime[0]=0;
    totalDistance=0;
    double distanceToFirst=distanceBetweenPoints(controlPoints[0], controlPoints[1]);
    
    for (int i=0; i<controlPoints.size()-1; i++) {
        
        totalDistance+=distanceBetweenPoints(controlPoints[i], controlPoints[i+1]);
        controlPointHitTime[i+1]=totalDistance;//vector will hold temporatly distances
        
        
    }
    
    double percentFirstDistance=1;
    if (totalDistance>0) {
        percentFirstDistance=distanceToFirst/totalDistance;
    }
    
    
    timeToSwitchSegment=percentFirstDistance*span;
    
    velocity=0;
    if (span>0) velocity=totalDistance/span;
    
    
    
    if (velocity!=0) {
        for (int i=0; i<controlPoints.size(); i++) {
            controlPointHitTime[i]/=velocity;//vector now holds times
        }
    }
    
    
    
    
}





vector<double> LG_LinearAnimation::directionVectorForSegment(LG_Point3D pt1,LG_Point3D pt2){
    
    vector<double> vect(3);
    
    vect[X_]=pt2[X_]-pt1[X_];
    vect[Y_]=pt2[Y_]-pt1[Y_];
    vect[Z_]=pt2[Z_]-pt1[Z_];
    
    normalize(vect);
    
    return vect;
    
    
}



void LG_LinearAnimation::configureRotation(const vector<double> &dir1,const vector<double> &dir2,LG_AnimationState *state){
    
    
    
    if (totalRotation != 0)return;
    
    vector<double> dir1_(dir1);
    vector<double> dir2_(dir2);
    
    dir2_[Y_]=0;
    dir1_[Y_]=0;
    
    
    
    if (vectorLenght(dir1_)==0 || vectorLenght(dir2_)==0) return;//dont rotate if one vector is with zero dimention
    normalize(dir1_);
    normalize(dir2_);
    
    
    double angle=angleBetween(dir1_, dir2_) / M_PI*180.;//otherwise just rotate like we used to!
    
    
    vector<double> rotationAxis=crossProduct(dir1_, dir2_);
    
    
    state->rotate(angle, rotationAxis[X_], rotationAxis[Y_], rotationAxis[Z_]);
    
    
    
    
    
    
    
}


//LAIGPROB2
void LG_LinearAnimation::applyRotByAnfParam(unsigned long timePassed, LG_AnimationState *state){
    
    
    double angle = (timePassed / (float)span)*totalRotation;
    state->rotate(angle, 0, 1, 0);
    
}


void LG_LinearAnimation::configureTranslation(double timeSinceAnimationStart,LG_AnimationState *state){
    
    
    
    int currentSegment= state->getCurrentSegment();
    double * lastPassedControlPoint=controlPoints[currentSegment];
    
    double timeSincePassedControlPoint=timeSinceAnimationStart-controlPointHitTime[currentSegment];
    //configureDirectionForCurrentSegment();
    
    
    vector<double> velocityVector(3);
    
    
    vector<double> directionVector=vectorBetweenPoints(controlPoints[currentSegment], controlPoints[currentSegment+1]);
    normalize(directionVector);
    
    
    velocityVector[X_]=directionVector[X_]*velocity;
    velocityVector[Y_]=directionVector[Y_]*velocity;
    velocityVector[Z_]=directionVector[Z_]*velocity;
    
    
    
    state->translate_afterRotation(lastPassedControlPoint[X_] + timeSincePassedControlPoint*velocityVector[X_], lastPassedControlPoint[Y_] + timeSincePassedControlPoint*velocityVector[Y_], lastPassedControlPoint[Z_] + timeSincePassedControlPoint*velocityVector[Z_]);
    
    
    
    
    
    
    
    
    
    
    
    
}