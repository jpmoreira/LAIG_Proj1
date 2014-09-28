//
//  LG_Node.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 23/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Node__
#define __LAIG_Proj1__LG_Node__

#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include "LG_Node.h"
#include <GL/glew.h>
//#include "LG_Properties.h"

#define LG_LightValue_Not_Set LG_INVALID_DOUBLE

#define LG_LightList_InitialValue {LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set}

#define LG_Matrix_InitialValue {LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue}


#define str_eq( value1 , value2 ) (strcmp(value1,value2)==0)

#define LG_Point_Length 3
#define LG_LightArray_Lenght 4


using  std::vector;
using std::string;
using std::map;

class LG_Node;//forward declaration for typedef


typedef map<string , LG_Node *> LG_Node_Map;
typedef vector<string *> LG_ID_Vector;
typedef std::pair<string , LG_Node *> LG_Node_Map_Pair;

typedef GLdouble LG_Point[3];
typedef GLdouble LG_LightArray[4];
typedef GLdouble LG_Matrix[4][4];




class LG_Node{
    
    
protected:
    
    
    
    /**
     
     A vector with all the nodes childs names
     
     */
    
    LG_ID_Vector childsIDs;
    
    
    /**
     
     The properties for this object
     
     */
    //LG_Properties *properties;
    
    
    /**
     
     
     The identifier for this node
     
     */
    
    string identifier;
    
    
    /**
     
     The map that has all the nodes;
     
     
     */
    
    
    LG_Node_Map *map;
    
    
    
public:
    
    
    /**
     
     Simple constructor. It automatically adds the node to the map
     
     */
    LG_Node(LG_Node_Map* theMap,string theIdentifier);
    
    
    
    /**
     
     
     A method to draw the node. Each Subclass should override this method.
     
     */
    
    virtual void draw();
    
    
    /**
     
     A method for getting a particular child from this node. First child is child number zero.
     
     */
    LG_Node * child(int childNr);
    
    
    /**
     
     A method for adding a child
     
     
     */
    
    
    void addChild(LG_Node *childToAdd);
    
    
    
    
    
    
};



#endif /* defined(__LAIG_Proj1__LG_Node__) */


