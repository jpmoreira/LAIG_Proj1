//
//  LG_Torus.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Torus.h"
#define _LG_Primitive_Name "_LG_Torus_"
#define LG_Torus_XML_Inner_Att_Name "inner"
#define LG_Torus_XML_Outer_Att_Name "outer"
#define LG_Torus_XML_Slices_Att_Name "slices"
#define LG_Torus_XML_Loops_Att_Name "loops"

int LG_Torus::_LG_classIDNr=0;

LG_Torus::LG_Torus(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier),ss_text(NULL),tt_text(NULL){
    
    
    
    //verify element name
    if (!str_eq(elem->Value(), LG_Torus_XML_Tag_Name)) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Torus_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Inner_Att_Name, elem, innerRadius);
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Outer_Att_Name, elem, outerRadius);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Loops_Att_Name, elem, loops);
    
    
    
    calculateCordinates();

}

LG_Torus::LG_Torus(LG_Node_Map *map,TiXmlElement *elem,LG_Appearance *app):LG_Primitive(map,autoIdentifier,app){
    
    
    //verify element name
    if (!str_eq(elem->Value(), LG_Torus_XML_Tag_Name)) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Torus_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Inner_Att_Name, elem, innerRadius);
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Outer_Att_Name, elem, outerRadius);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Loops_Att_Name, elem, loops);
    
    
    
    
    
}



LG_Torus::LG_Torus(LG_Node_Map *map,double inner,double outer,int sl,int loop):LG_Primitive(map,autoIdentifier){


}


#pragma mark - Inherited Methods
void LG_Torus::draw()
{
    
    LG_Primitive::draw();
    
    
    
    
    
    
    glBegin(GL_QUADS);
     
    
    
    
    for (int i=0; i<loops; i++) {
        
        
        for (int f=0; f<slices; f++) {
            
            
            
            
            
            
            glTexCoord2d(ss_text[i*(slices+1)+f+1], tt_text[i*(slices+1)+f+1]);
            glNormal3d(xx_normal[i*(slices+1)+f+1], yy_normal[i*(slices+1)+f+1],zz_normal[i*(slices+1)+f+1]);
            glVertex3d(xx[i*(slices+1)+f+1], yy[i*(slices+1)+f+1],zz[i*(slices+1)+f+1]);
            
            
            glTexCoord2d(ss_text[(i+1)*(slices+1)+f+1], tt_text[(i+1)*(slices+1)+f+1]);
            glNormal3d(xx_normal[(i+1)*(slices+1)+f+1], yy_normal[(i+1)*(slices+1)+f+1],zz_normal[(i+1)*(slices+1)+f+1]);
            glVertex3d(xx[(i+1)*(slices+1)+f+1], yy[(i+1)*(slices+1)+f+1],zz[(i+1)*(slices+1)+f+1]);
            
            
            glTexCoord2d(ss_text[(i+1)*(slices+1)+f], tt_text[(i+1)*(slices+1)+f]);
            glNormal3d(xx_normal[(i+1)*(slices+1)+f], yy_normal[(i+1)*(slices+1)+f],zz_normal[(i+1)*(slices+1)+f]);
            glVertex3d(xx[(i+1)*(slices+1)+f], yy[(i+1)*(slices+1)+f],zz[(i+1)*(slices+1)+f]);
            

            glTexCoord2d(ss_text[i*(slices+1)+f], tt_text[i*(slices+1)+f]);
            glNormal3d(xx_normal[i*(slices+1)+f], yy_normal[i*(slices+1)+f],zz_normal[i*(slices+1)+f]);
            glVertex3d(xx[i*(slices+1)+f], yy[i*(slices+1)+f],zz[i*(slices+1)+f]);
            
            
            
            
            
            
           
            
            
            
        }
    }
    
    
    glEnd();
     
    
    
    
     
    
}


void LG_Torus::calculateTextureCoordinates(){


    if (!ss_text) {
        ss_text=(double *)calloc((loops+1)*(slices+1),sizeof(double));
        tt_text=(double *)calloc((loops+1)*(slices+1),sizeof(double));
    }
    if (!LG_Appearance::currentTexture)return;
    
    
    
    
    double alpha=0;//angle related to loops(around yy axis)
    double beta=0;//angle around each loop internal loop axis
    double delta_apha=-2.0*M_PI/loops;
    double delta_beta=2.0*M_PI/slices;
    
    
    double r1=outerRadius;
    double r2=innerRadius;
    
    double loopPerimeter=2*M_PI*r2;
    
    
    
    double torusExternalPerimeter=2*M_PI*(r1+r2);
    
    double s_lenght=0;
    double t_lenght=0;
    
    s_lenght=LG_Appearance::currentTexture->getLength_s();
    t_lenght=LG_Appearance::currentTexture->getLength_t();
    
    
    double nrRepetitionsAlongLoop=loopPerimeter/s_lenght;
    
    double nrRepsAlongWholeTorus=torusExternalPerimeter/t_lenght;
    
    
    
    for (int l=0; l<=loops; l++) {
        
        
        
        beta=0;
        for (int s=0; s<=slices; s++) {
            
            
        
            tt_text[l*(slices+1)+s]=beta/(2.0*M_PI)*nrRepetitionsAlongLoop;
            ss_text[l*(slices+1)+s]=alpha/(2.0*M_PI)*nrRepsAlongWholeTorus;
            
            
            
            beta+=delta_beta;
        }
        
        
        alpha+=delta_apha;
    }
    
    
    
    
    
    
    
    
    

    
}


#pragma mark - Helper Methods


void LG_Torus::calculateCordinates(){

    
    
    xx=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    yy=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    zz=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    
    
    xx_normal=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    yy_normal=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    zz_normal=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    
   
    
    double alpha=0;//angle related to loops(around yy axis)
    double beta=0;//angle around each loop internal loop axis
    double delta_apha=-2.0*M_PI/loops;
    double delta_beta=2.0*M_PI/slices;

    
    double r1=outerRadius;
    double r2=innerRadius;

    
    for (int l=0; l<=loops; l++) {
        
        
        
        beta=0;
        for (int s=0; s<=slices; s++) {
            
            
            
            
    
            
            xx[l*(slices+1)+s]=r1*cos(alpha)+r2*cos(beta)*cos(alpha);
            yy[l*(slices+1)+s]=r1*sin(alpha)+r2*cos(beta)*sin(alpha);
            zz[l*(slices+1)+s]=r2*sin(beta);
            
        
            
            xx_normal[l*(slices+1)+s]=cos(beta)*cos(alpha);
            yy_normal[l*(slices+1)+s]=cos(beta)*sin(alpha);
            zz_normal[l*(slices+1)+s]=sin(beta);
            
            
            
            
            beta+=delta_beta;
        }
        
        
        alpha+=delta_apha;
    }
    
    

    
    
    

    

}