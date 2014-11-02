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

LG_LinearAnimation::LG_LinearAnimation(LG_Node_Map *map,string identifier,vector<double *> points,double duration):LG_Animation(map,identifier,duration),controlPoints(points),currentSegment(0){
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)rotation_matrix);
    glTranslated(controlPoints[0][0], controlPoints[0][1], controlPoints[0][2]);//place at the start control point
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)translation_matrix);
    
    configureInitialParameters();
}

LG_LinearAnimation::LG_LinearAnimation(LG_Node_Map *map,TiXmlElement *element):LG_Animation(map,element),controlPoints(vector<double *>()),currentSegment(0){


    handleControlPoints(element);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)rotation_matrix);//rotation matrix always starts as identity
    glTranslated(controlPoints[0][0], controlPoints[0][1], controlPoints[0][2]);//place at the start control point
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)translation_matrix);
    
    configureInitialParameters();
    
    
    
}


#pragma mark - Animation Application


void LG_LinearAnimation::apply(){
    
    
    glMultMatrixd((GLdouble *)rotation_matrix);
    glMultMatrixd((GLdouble *)translation_matrix);

    

}


void LG_LinearAnimation::update(long timeNow){
    
    
    

    
    
    
    if (startTime<0) {
        startTime=timeNow;
        return;
    }
    else if (timeNow>startTime+span) timeNow=startTime+span;
    
    double timeSinceStart=timeNow-startTime;

    if (timeToSwitchSegment<timeSinceStart) {//if time to switch segments has passed
        
        vector<double> segmentWeAreIn=directionVectorForSegment(controlPoints[currentSegment], controlPoints[currentSegment+1]);
        
        vector<double> segmentWeAreGoingTo=directionVectorForSegment(controlPoints[currentSegment], controlPoints[currentSegment+1]);
        
        configureRotation(controlPoints[currentSegment], controlPoints[currentSegment+1], controlPoints[currentSegment+2]);
        
        timeToSwitchSegment+=vectorLenght(segmentWeAreGoingTo)/velocity;
        
        currentSegment++;//we are no longer in the same segment
        
    }
    
    
    
    configureTranslation(timeSinceStart);
    
    


    

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


void LG_LinearAnimation::configureInitialParameters(){


    controlPointHitTime=vector<double>(controlPoints.size());
    controlPointHitTime[0]=0;
    currentSegment=0;
    totalDistance=0;
    double distanceToFirst=distanceBetweenPoints(controlPoints[0], controlPoints[1]);
    
    for (int i=0; i<controlPoints.size()-1; i++) {
        
        totalDistance+=distanceBetweenPoints(controlPoints[i], controlPoints[i+1]);
        controlPointHitTime[i+1]=totalDistance;//vector will hold temporatly distances
        
        
    }
    
    double percentFirstDistance=distanceToFirst/totalDistance;
    
    timeToSwitchSegment=percentFirstDistance*span;
    
    velocity=totalDistance/span;
    
    for (int i=0; i<controlPoints.size(); i++) {
        controlPointHitTime[i]/=velocity;//vector now holds times
    }
    
    configureDirectionForCurrentSegment();


}



void LG_LinearAnimation::configureDirectionForCurrentSegment(){

    
    if (currentSegment+1>=controlPoints.size()) return;
    
    vector<double> vect=directionVectorForSegment(controlPoints[currentSegment], controlPoints[currentSegment+1]);

    normalize(vect);
    directionVector[X_]=vect[X_];
    directionVector[Y_]=vect[Y_];
    directionVector[Z_]=vect[Z_];
    


}

vector<double> LG_LinearAnimation::directionVectorForSegment(LG_Point3D pt1,LG_Point3D pt2){

    vector<double> vect(3);
    
    vect[X_]=pt2[X_]-pt1[X_];
    vect[Y_]=pt2[Y_]-pt1[Y_];
    vect[Z_]=pt2[Z_]-pt1[Z_];
    
    normalize(vect);
    
    return vect;


}

void LG_LinearAnimation::configureRotation(LG_Point3D previousSegmentStart,LG_Point3D borderPoint,LG_Point3D nextSegmentFinish){
    
    
    
    vector<double> dir1=directionVectorForSegment(previousSegmentStart, borderPoint);
    vector<double> dir2=directionVectorForSegment(borderPoint, nextSegmentFinish);
    
    double angle=angleBetween(dir1, dir2)/M_PI*180.;
    
    vector<double> rotationAxis=crossProduct(dir1, dir2);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotated(angle, rotationAxis[X_], rotationAxis[Y_], rotationAxis[Z_]);
    glMultMatrixd((GLdouble *)rotation_matrix);
    
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)rotation_matrix);
    
    
    
    


}


void LG_LinearAnimation::configureTranslation(double timeSinceAnimationStart){


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    double * lastPassedControlPoint=controlPoints[currentSegment];
    
    double timeSincePassedControlPoint=timeSinceAnimationStart-controlPointHitTime[currentSegment];
    configureDirectionForCurrentSegment();
    
    
    glTranslated(lastPassedControlPoint[X_]+directionVector[X_]*timeSincePassedControlPoint*velocity, lastPassedControlPoint[Y_]+directionVector[Y_]*timeSincePassedControlPoint*velocity, lastPassedControlPoint[Z_]+directionVector[Z_]*timeSincePassedControlPoint*velocity);
    
    glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble *)translation_matrix);
    
    
    


}