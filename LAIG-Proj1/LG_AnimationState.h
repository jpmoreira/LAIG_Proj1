//
//  LG_AnimationState.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 17/11/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_AnimationState__
#define __LAIG_Proj1__LG_AnimationState__

#include <stdio.h>

#include "LG_Animation.h"

class LG_AnimationState {
    
    
    friend class LG_Animation;
    unsigned long startTime;
    double rotation_matrix[4][4];
    double translation_matrix[4][4];
    double post_rotation_translation_matrix[4][4];
    LG_Animation *animation;
    int currentSegment;
    bool started;
    
    
public:
    LG_AnimationState(LG_Node_Map *map,TiXmlElement *elem);
    
    LG_AnimationState(LG_Node_Map *map,LG_Animation *anim);
    
    virtual bool finished(unsigned long timeNow);
    void update(unsigned long timeNow);
    void apply();
    
    int getCurrentSegment();

    void incrementCurrentSegment();
    
    void rotate(double angle,double x,double y,double z);
    void translate(double x,double y,double z);
    void translate_afterRotation(double x,double y,double z);
    
    unsigned long timePassed(unsigned long timeNow);
};

#endif /* defined(__LAIG_Proj1__LG_AnimationState__) */
