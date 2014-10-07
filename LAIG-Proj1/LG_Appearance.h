//
//  LG_Appearance.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Appearance__
#define __LAIG_Proj1__LG_Appearance__

#include "LG_Parsable_Node.h"
#define LG_Appearance_XML_Tag_Name "appearance"
#define LG_Appearance_ID_XML_Att_Name "id"
class LG_Appearance: public LG_Parsable_Node{
    
    
private:
    
    LG_LightArray ambient;
    LG_LightArray diffuse;
    LG_LightArray specular;
    double shininess;
    
     string getIdentifier(TiXmlElement *elem);
    
    void handleComponent(TiXmlElement *component);
    void initializeComponents();
    
public:
    
    LG_Appearance(LG_Node_Map *map,TiXmlElement *elem);
    
    LG_Appearance(LG_Node_Map *map,LG_LightArray amb,LG_LightArray diff,LG_LightArray spec,double s,string identif);
    
    
    
    
    
   
    
};
#endif /* defined(__LAIG_Proj1__LG_Appearance__) */
