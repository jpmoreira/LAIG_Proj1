//
//  LG_Primitive.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 28/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Primitive.h"

#define LG_Point_Comparision_Gap 0.0001//the maximum allowed difference between two point's componenets for them to be considered equal


#pragma mark - Constructors

LG_Primitive::LG_Primitive(LG_Node_Map *map,string indentif):LG_Parsable_Node(map,indentif){


}


#pragma mark - Initializations


void LG_Primitive::initializePoint(LG_Point &point){

    for (int i=0; i<LG_Point_Length; i++) {
        point[i]=LG_INVALID_DOUBLE;
    }
    

}

#pragma mark - Helper Methods

bool LG_Primitive::equalPoints(LG_Point &pt1, LG_Point &pt2){
    
    
    for (int i=0; i<LG_Point_Length; i++) {
        if (abs(pt1[i]-pt2[i])>=LG_Point_Comparision_Gap)return false;
    }
            
    return true;

}
