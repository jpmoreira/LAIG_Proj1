//
//  LG_Triangle.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Triangle__
#define __LAIG_Proj1__LG_Triangle__

#include <stdio.h>
#include "LG_Node.h"

#endif /* defined(__LAIG_Proj1__LG_Triangle__) */


class LG_Triangle : public LG_Node {
    
    
    
private:
    
    LG_Point pt1;
    LG_Point pt2;
    LG_Point pt3;
    
    /**
     
     Copies all the points to the object containers that are supposed to hold it
     
     */
    
    void copyPoints(LG_Point pt1,LG_Point pt2, LG_Point pt3);
    
    
public:
    
    
    
   
    /**
     
     Simple constructor for the triangle Node. It initializes the map and sets the points for the triangle
     
     */
    
    LG_Triangle(LG_Node_Map *map,LG_Point pt1,LG_Point pt2, LG_Point pt3);

    
    
     virtual void draw();
    
    
    
    
    
    
};