//
//  LG_Appearance.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Appearance__
#define __LAIG_Proj1__LG_Appearance__

#include "LG_Texture.h"

#include <CGFappearance.h>
#define LG_Appearance_XML_Tag_Name "appearance"
#define LG_Appearance_ID_XML_Att_Name "id"
class LG_Appearance: public LG_Parsable_Node{
    
    
private:
    
    
    LG_Texture *texture;
    LG_LightArray_f ambient;
    LG_LightArray_f diffuse;
    LG_LightArray_f specular;
    float shininess;

    
   
    
    
    float _savedShininess;
    LG_LightArray_f _savedAmbient;
    LG_LightArray_f _savedSpecular;
    LG_LightArray_f _savedDiffuse;
    
    LG_Texture * _savedCurrentTexture;
    
    
    
    
     string getIdentifier(TiXmlElement *elem);
    
    void handleComponent(TiXmlElement *component);
    
    /**
     
     A method for handling the parsing of the texture attribute on an appearance
     
     
     */
    void handleTextureRef (LG_Node_Map *texturesMap,TiXmlElement *element);
    void initializeComponents();
    

    
public:
    
     static LG_Texture *currentTexture;
    
    LG_Appearance(LG_Node_Map *map,TiXmlElement *elem,LG_Node_Map *texturesMap);
    
    LG_Appearance(LG_Node_Map *map,LG_LightArray_f amb,LG_LightArray_f diff,LG_LightArray_f spec,float s,string identif,LG_Texture *texture);
    
    /**
     
     
     A method for applying the appearance
     
     */
    void apply();
    
    
    
    /**
     
     
     A method for disapplying the apperance
     
     */
    void unapply();
    
    
    LG_Texture * getTexture();
    
    
    
};
#endif /* defined(__LAIG_Proj1__LG_Appearance__) */
