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

LG_Primitive::LG_Primitive(LG_Node_Map *map,string identif,LG_Appearance *app):LG_Parsable_Node(map,identif),app(app){

}


#pragma mark - Initializations


void LG_Primitive::initializePoint3D(LG_Point3D &point){

    for (int i=0; i<LG_Point3D_Length; i++) {
        point[i]=LG_INVALID_DOUBLE;
    }
    

}

#pragma mark - Helper Methods

bool LG_Primitive::equalPoints(LG_Point3D &pt1, LG_Point3D &pt2){
    
    
    for (int i=0; i<LG_Point3D_Length; i++) {
        if (abs(pt1[i]-pt2[i])>=LG_Point_Comparision_Gap)return false;
    }
            
    return true;

}

void LG_Primitive::newells(LG_Point3D p1,LG_Point3D p2,LG_Point3D p3, LG_Point3D normal){

    
    LG_Point3D u;
    LG_Point3D v;
    
    u[0]=p2[0]-p1[0];
    u[1]=p2[1]-p1[1];
    u[2]=p2[2]-p1[2];
    
    v[0]=p3[0]-p1[0];
    v[1]=p3[1]-p1[1];
    v[2]=p3[2]-p1[2];
    
    normal[0]=u[1]*v[2]-u[2]*v[1];
    normal[1]=u[2]*v[0]-u[0]*v[2];
    normal[2]=u[0]*v[1]-u[1]*v[0];
    
    double dimention=sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);
    
    normal[0]/=dimention;
    normal[1]/=dimention;
    normal[2]/=dimention;
    

}


double * LG_Primitive::newells(vector<double *> &points){
    
    
    double * normal =(double *) calloc(3,sizeof(double));
    
    for (int i = 0; i < points.size(); i++) {
        
        
        double * current = (double *)points[i];// { 0... m }
        double * next = (double *)points[(i+1) % points.size()]; // { 1 ... m,1 }
        
        
        
        normal[0] += ((current[1]- next[1]) * (current[2] + next[2]));
        normal[1] += ((current[2] - next[2]) * (current[0] + next[0]));
        normal[2] += ((current[0] - next[0]) * (current[1] + next[1]));
        
   
    }
    
    double modulus=sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);
    
    normal[0]/=modulus;
    normal[1]/=modulus;
    normal[2]/=modulus;
    
    return normal;
}


#pragma mark - Inherited Methods


void LG_Primitive::draw(){
    
    calculateTextureCoordinates();


}


void LG_Primitive::config(){

    calculateTextureCoordinates();
}
