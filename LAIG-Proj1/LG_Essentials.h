//
//  LG_Essentials.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 07/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef LAIG_Proj1_LG_Essentials_h
#define LAIG_Proj1_LG_Essentials_h


#include <map>
#include <string>
#include <vector>
#include <tinyxml.h>
//#include <GL/glew.h>


#define LG_LightValue_Not_Set LG_INVALID_DOUBLE

#define LG_LightList_InitialValue {LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set}

#define LG_Matrix_InitialValue {LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue}


#define str_eq( value1 , value2 ) (strcmp(value1,value2)==0)

#define LG_Point3D_Length 3
#define LG_Point2D_Length 2
#define LG_LightArray_Lenght 4
#define LG_Matrix_Dimention 4

using  std::vector;
using std::string;
using std::map;

class LG_Node;

typedef map<string , LG_Node *> LG_Node_Map;
typedef vector<string> LG_ID_Vector;
typedef std::pair<string , LG_Node *> LG_Node_Map_Pair;



typedef double LG_Point3D[3];
typedef double LG_Point2D[2];
typedef double LG_LightArray[4];
typedef double LG_Matrix[4][4];
typedef float LG_LightArray_f[4];


#endif
