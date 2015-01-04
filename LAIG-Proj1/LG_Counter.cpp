//
//  LG_Counter.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 03/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_Counter.h"

#define nrTextureExtension ".jpg"
#define nrTexturePath "../data/nr"
#define nrComponents {0.9,0.9,0.9,1.0}
#define nrShininess 0.01

 vector<LG_Appearance *> LG_Counter::nrApps=vector<LG_Appearance *>();
 LG_Node_Map LG_Counter::nrAppsMap=LG_Node_Map();

LG_Counter::LG_Counter(LG_Node_Map *map,string id):LG_Primitive(map,id){

    if (nrApps.size()==0) initializeNrApps();
}


void LG_Counter::initializeNrApps(){

    LG_LightArray_f f=nrComponents;

    LG_Texture *text=new LG_Texture(&nrAppsMap, "../data/nr0.jpg", nrWidth, nrHeight, "nr0");
    LG_Appearance * app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr0App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr1.jpg", nrWidth, nrHeight, "nr1");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr1App",text);

    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr2.jpg", nrWidth, nrHeight, "nr2");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr2App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr3.jpg", nrWidth, nrHeight, "nr3");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr3App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr4.jpg", nrWidth, nrHeight, "nr4");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr4App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr5.jpg", nrWidth, nrHeight, "nr5");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr5App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr6.jpg", nrWidth, nrHeight, "nr6");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr6App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr7.jpg", nrWidth, nrHeight, "nr7");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr7App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr8.jpg", nrWidth, nrHeight, "nr8");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr8App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/nr9.jpg", nrWidth, nrHeight, "nr9");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"nr9App",text);
    
    nrApps.push_back(app);
    
    text=new LG_Texture(&nrAppsMap, "../data/clockSeparator.jpg", nrWidth, nrHeight, "clockSeparator");
    app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,"clockSeparatorApp",text);
    
    nrApps.push_back(app);
    
    /*
    for (int i=1; i<=9; i++) {
        
        string textureName=std::to_string(i);
        string textureID="LG_NrTexture_"+textureName;
        string appearanceID="LG_NrApp_"+textureName;
        
        //LG_LightArray_f f=nrComponents;
        
        textureName=nrTexturePath+textureName+nrTextureExtension;

        LG_Texture *text=new LG_Texture(&nrAppsMap, textureName, 1, 1, textureID);
        LG_Appearance * app=new LG_Appearance(&nrAppsMap,f,f,f,nrShininess,appearanceID,text);
        
        nrApps.push_back(app);
    }
     */

}
