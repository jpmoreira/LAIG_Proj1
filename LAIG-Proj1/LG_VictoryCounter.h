//
//  LG_VictoryCounter.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_VictoryCounter__
#define __LAIG_Proj1__LG_VictoryCounter__

#include <stdio.h>
#include "LG_Counter.h"

#define LG_VictoryCounter_XML_Tag_Name "counter"
#define LG_VictoryCounter_ID "LG_VictoryCounter_ID"

class LG_VictoryCounter:public LG_Counter {
    
    
    LG_Appearance * appForFirstPlayerVictories1;
    LG_Appearance * appForFirstPlayerVictories2;
    LG_Appearance * appForSecondPlayerVictories1;
    LG_Appearance * appForSecondPlayerVictories2;
    
public:
    LG_VictoryCounter(LG_Node_Map *map,TiXmlElement * elem);
    
    void draw(bool selectMode);
    
    void reset();
    
    void updateNrVictories(int nrVictoriesA,int nrVictoriesB);
};

#endif /* defined(__LAIG_Proj1__LG_VictoryCounter__) */
