//
//  LG_Culling.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 26/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Culling__
#define __LAIG_Proj1__LG_Culling__

#include <stdio.h>


#define _LG_Culling_NodeID "_LG_Culling"

#include "LG_Parsable_Node.h"


#define LG_Culling_Back_String "back"
#define LG_Culling_Front_String "front"
#define LG_Culling_None_String "none"
#define LG_Culling_Both_String "both"

typedef enum{

    LG_Back,
    LG_Front,
    LG_None,
    LG_Both,
    LG_Culling_Face_Not_Set

} LG_Culling_Face;


typedef enum{

    LG_Culling_Order_CW,
    LG_Culling_Order_CCW,
    LG_Culling_Order_Not_Set
} LG_Culling_Order;

class LG_Culling : public LG_Parsable_Node{
    
private:
    
    LG_Culling_Order order;
    LG_Culling_Face face;
    
public:
    
    
    
    LG_Culling(LG_Node_Map *map,TiXmlElement *element);
	LG_Culling(LG_Node_Map *map, TiXmlElement *element, LG_Culling_Order order, LG_Culling_Face face);
    
	void verifyAttributesAndValues(TiXmlElement *element);
	void verifyElementName(TiXmlElement *element);
	void stringToAttr(string *att_name, char *string);
    
};
#endif /* defined(__LAIG_Proj1__LG_Culling__) */
