//
//  LG_Counter.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Counter__
#define __LAIG_Proj1__LG_Counter__

#include <stdio.h>
#include "LG_Primitive.h"

#define nrHeight 0.02
#define nrWidth 0.012


class LG_Counter:public LG_Primitive {
    
    
    

    
public:
    LG_Counter(LG_Node_Map *map,string identif);
    static vector<LG_Appearance *> nrApps;
    static LG_Node_Map nrAppsMap;
    static void initializeNrApps();
    
    virtual void reset()=0;
};

#endif /* defined(__LAIG_Proj1__LG_Counter__) */
