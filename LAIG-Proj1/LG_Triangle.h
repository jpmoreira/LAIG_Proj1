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
#include "LG_Primitive.h"

#define LG_Triangle_XML_Tag_Name "triangle"

#define LG_Origin_3D_Point {0,0,0}

#endif /* defined(__LAIG_Proj1__LG_Triangle__) */


class LG_Triangle : public LG_Primitive {
    
    
    
private:
    
    LG_Point3D pt1;
    LG_Point3D pt2;
    LG_Point3D pt3;
    
    /**
     Number that holds the current id for the newly created primitive instance. Used in the autoIdentifier macro
     
     */
    
    static int _LG_classIDNr;
    
    /**
     
     Copies all the points to the object data members that are supposed to hold them
     
     */
    
    void copyPoints(LG_Point3D pt1,LG_Point3D pt2, LG_Point3D pt3);
    
    
    
    
public:
    
    
    
    /**
     
     Constructor that takes a TiXmlElement, validates it and attemps to create a LG_Triangle object, in case some error occurs the correct LG_Parse_Exception subclass object is thrown
     
     */
    LG_Triangle(LG_Node_Map *map,TiXmlElement *elem);
    
    
   
    /**
     
     Simple constructor for the triangle Node. It initializes the map and sets the points for the triangle
     
     */
    
    LG_Triangle(LG_Node_Map *map,string identif,LG_Point3D pt1,LG_Point3D pt2, LG_Point3D pt3);

    
    /**
     
     Simple constructor that creates a triangle with all three vertexes at the origin
     
     */
    LG_Triangle(LG_Node_Map *map,string identif);
    
    virtual void draw();
    
    

    
    
    
};