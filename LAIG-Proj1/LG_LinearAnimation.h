//
//  LG_LinearAnimation.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_LinearAnimation__
#define __LAIG_Proj1__LG_LinearAnimation__

#include <stdio.h>

#include "LG_Animation.h"

class LG_LinearAnimation:public LG_Animation {
    
    
private:
    vector<double *>controlPoints;
    /**
     
     vector that hold the information about the time since animation beging when a given controlPoint should be hit
     */
    vector<double> controlPointHitTime;
    
    
    double velocity;
    double timeToSwitchSegment;
    double totalDistance;
    double totalRotation;
    
    
    
    void handleControlPoints(TiXmlElement *animationElement);
    
    
    static double distanceBetweenPoints(LG_Point3D pt1,LG_Point3D pt2);
    
    /**
     
     Configures the parameters for the animation based on the control points
     
     */
    void configureInitialParameters(LG_AnimationState *state);
    

    /**
     
     Returns an array with the direction vector for a given vector.
     */
    
    vector<double> directionVectorForSegment(LG_Point3D pt1,LG_Point3D pt2);
    
    
    
    /**
     
     Configures the current matrix to include a rotation to the new segment.
     */
    void configureRotation(const vector<double> &dir1,const vector<double> &dir2,LG_AnimationState *state);
    
    
    void configureTranslation(double  timeSinceAnimationStart,LG_AnimationState *state);
    
public:
    
    LG_LinearAnimation(LG_Node_Map *map,string identifier,vector<double *> points,double duration);
    
    LG_LinearAnimation(LG_Node_Map *map,TiXmlElement *elem);
    void apply();
    void update(unsigned long timeNow,LG_AnimationState *state);
    
    
    //LAIGPROB2
    void applyRotByAnfParam(unsigned long timePassed, LG_AnimationState *state);
    
    
};


#endif /* defined(__LAIG_Proj1__LG_LinearAnimation__) */