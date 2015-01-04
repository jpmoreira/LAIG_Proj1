//
//  LG_Clock.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Clock__
#define __LAIG_Proj1__LG_Clock__

#include <stdio.h>
#include "LG_Counter.h"

#define LG_Clock_XML_Tag_Name "clock"
#define LG_Clock_ID "LG_Clock_ID"

class LG_Clock: public LG_Counter {
    
    
    
    
    unsigned int seconds;
    unsigned int minutes;
    unsigned long startTime;
    
    LG_Appearance * appForHours2;
    LG_Appearance * appForHours1;
    LG_Appearance * appForSeconds1;
    LG_Appearance * appForSeconds2;
    
    LG_Appearance * appSeparator;
    
    bool started;
    
public:
    
    LG_Clock(LG_Node_Map *map ,TiXmlElement *elem);
    
    void draw(bool selectMode);
    void update(unsigned long timeNow);
    
    void calculateTextureCoordinates();
    
    void reset();
};

#endif /* defined(__LAIG_Proj1__LG_Clock__) */
