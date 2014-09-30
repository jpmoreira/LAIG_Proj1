//
//  LG_Transform.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 30/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Transform__
#define __LAIG_Proj1__LG_Transform__

#include "LG_Parsable_Node.h"



class LG_Transform:public LG_Parsable_Node{
    
    
private:
    
    LG_Matrix matrix;
    
    
    static int _LG_classIDNr;
    
    
    
    /**
     
     A method that returns the matrix in a given transformation tag. Verifies tag names.
     
     */
    static void applyMatrixForTransform(TiXmlElement *element);
    static void applyRotation(TiXmlElement *element);
    static void applyTranslation(TiXmlElement *element);
    static void applyScaling(TiXmlElement *element);
    
    
    
    static bool isTranslation(TiXmlElement *elem);
    static bool isRotation(TiXmlElement *elem);
    static bool isScale(TiXmlElement *elem);
    
    
    static void copyMatrix(LG_Matrix origin ,LG_Matrix destination);
    
public:
    
    LG_Transform(LG_Node_Map *map,TiXmlElement *elem);
    LG_Transform(LG_Node_Map *map,LG_Matrix m);


    
};

#endif /* defined(__LAIG_Proj1__LG_Transform__) */
