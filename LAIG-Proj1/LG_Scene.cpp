//
//  LG_Scene.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 11/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Scene.h"

#include "CGFaxis.h"
#include "CGFapplication.h"
#include <math.h>
#include <iostream>
#include "LG_Appearance.h"



void LG_Scene::setDocName(string name){
    
    docName=name;
}

void LG_Scene::init() {
    
    TiXmlDocument *doc = new TiXmlDocument(docName.c_str());
    
    
    
    if(!doc->LoadFile()){
        
        std::cout<<"Unable to load file named "<<docName<<"."<<std::endl;
        std::cout<<"Execution will be aborted"<<std::endl;
        exit(EXIT_FAILURE);
        
    }
    
    
    
    anf=LG_ANF::anfForXML(doc);
    
    //anf=new LG_ANF(doc->FirstChildElement());
    
    
    
    
    //CGFscene::activeCamera=anf->currentCamera();
    
    //glEnable(GL_LIGHTING);
    
    
    // Define ambient light (do not confuse with ambient component of individual lights)
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
    
    
    // Declares and enables two lights, with null ambient component
    
    //light0 = new CGFlight(GL_LIGHT0, light0_pos);
    //light0->setAmbient(ambientNull);
    //light0->setSpecular(yellow);
    //
    //
    //
    ////light1 = new CGFlight(GL_LIGHT1, light1_pos);
    //light1 = new CGFlight(GL_LIGHT1, light1_pos);
    //light1->setAmbient(ambientNull);
    //
    //
    //light1->setKc(1);
    //light1->setKl(0);
    //light1->setKq(0);
    //
    //
    ////light2 = new CGFlight(GL_LIGHT2, light2_pos);
    //light2 = new CGFlight(GL_LIGHT2, light2_pos);;
    //light2->setAmbient(ambientNull);
    //
    //
    //
    //light2->setKc(1);
    //light2->setKl(0);
    //light2->setKq(0);
    //
    //
    //light3 = new CGFlight(GL_LIGHT3, light3_pos);
    //light3->setAmbient(ambientNull);
    //
    //
    //
    //
    //light3->setKc(0);
    //light3->setKl(0);
    //light3->setKq(0.2);
    //
    //
    //light0->enable();
    //light1->enable();
    //light2->disable();
    //light3->disable();
    // Uncomment below to enable normalization of lighting normal vectors
    glEnable (GL_NORMALIZE);
    
    setUpdatePeriod(100);
    
    
    anf->config();
    
    
    
}


void LG_Scene::display(){
    
    
    anf->selective_config();
    
    // ---- BEGIN Background, camera and axis setup
    
    // Clear image and depth buffer everytime we update the scene
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode(GL_MODELVIEW);
    
    
    glLoadIdentity();
    
    // Apply transformations corresponding to the camera position relative to the origin
    
    /*
     if (CGFscene::activeCamera!=anf->currentCamera()) {
     CGFscene::activeCamera=anf->currentCamera();
     CGFapplication::activeApp->forceRefresh();
     }
     */
    
    
    CGFscene::activeCamera->applyView();
    
    // Draw axis
    axis.draw();
    
    anf->draw();

    setUpdatePeriod(20);
    glutSwapBuffers();
    
    
}

void LG_Scene::update(unsigned long millis){
    
    anf->getAnimations()->update(millis);
    
    anf->graph->update(millis);
}

LG_ANF *LG_Scene::getAnf()
{
    return anf;
}