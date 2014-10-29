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
    
    
    
    
    void handleControlPoints(TiXmlElement *animationElement);
    
    
public:
    
    LG_LinearAnimation(LG_Node_Map *map,string identifier,vector<double *> points,double duration);
    
    LG_LinearAnimation(LG_Node_Map *map,TiXmlElement *elem);
    void apply(long int timeElapsed);
    
};


#endif /* defined(__LAIG_Proj1__LG_LinearAnimation__) */
