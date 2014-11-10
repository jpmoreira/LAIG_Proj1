//
//  LG_Scene.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 11/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Scene__
#define __LAIG_Proj1__LG_Scene__

#include <stdio.h>

#include <CGFscene.h>
#include "LG_ANF.h"

class LG_Scene:public CGFscene {
    
    
    
    LG_ANF *anf;
    string docName;
    
    //CGFlight* light0;
    //CGFlight* light1;
    //CGFlight* light2;
    //CGFlight* light3;
    
    
public:
    void init();
    void display();
    void update(unsigned long millis);
    void setDocName(string name);
	LG_ANF *getAnf();
};




#endif /* defined(__LAIG_Proj1__LG_Scene__) */
