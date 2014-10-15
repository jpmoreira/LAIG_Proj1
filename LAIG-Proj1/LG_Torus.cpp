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

LG_Torus::LG_Torus(LG_Node_Map *map,TiXmlElement *elem):LG_Primitive(map,autoIdentifier){
    
    
    
    //verify element name
    if (!str_eq(elem->Value(), LG_Torus_XML_Tag_Name)) {
        throw  new LG_Parse_Exception_Wrong_Element_Name(new string(LG_Torus_XML_Tag_Name),new string(elem->Value()));
    }
    
    
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Inner_Att_Name, elem, innerRadius);
    positiveDouble_tryToAttributeVariable(LG_Torus_XML_Outer_Att_Name, elem, outerRadius);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Slices_Att_Name, elem, slices);
    positiveInt_tryToAttributeVariable(LG_Torus_XML_Loops_Att_Name, elem, loops);
    
    
    
    

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
    
    
    
    
	//glutSolidTorus(this->innerRadius, this->outerRadius, this->slices, this->loops);
    

    
     
    
    
    
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     
    
    
    
     
    
}


void LG_Torus::calculateTextureCoordinates(){


    static bool ok=false;
    
    if (!ok) {
        ok=true;
        calculateCordinates();
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
    
    ss_text=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    tt_text=(double *)malloc(sizeof(double)*(loops+1)*(slices+1));
    
    double alpha=0;//angle related to loops(around yy axis)
    double beta=0;//angle around each loop internal loop axis
    double delta_apha=-2.0*M_PI/loops;
    double delta_beta=2.0*M_PI/slices;

    
    double r1=outerRadius;
    double r2=innerRadius;
    
    double loopPerimeter=2*M_PI*r2;
    double torusPerimeter=2*M_PI*r1;
    
    
    double s_lenght=0;
    double t_lenght=0;
    
    if (LG_Appearance::currentTexture) {
        s_lenght=LG_Appearance::currentTexture->getLength_s();
        t_lenght=LG_Appearance::currentTexture->getLength_t();
    }
    
    
    

    for (int l=0; l<=loops; l++) {
        
        double t_distFromStartOfLoop=l/(float)loops*torusPerimeter;
        
        beta=0;
        for (int s=0; s<=slices; s++) {
            
            double s_distFromStartOfLoop=s/(float)slices*loopPerimeter;
            
            
    
            
            xx[l*(slices+1)+s]=r1*cos(alpha)+r2*cos(beta)*cos(alpha);
            yy[l*(slices+1)+s]=r1*sin(alpha)+r2*cos(beta)*sin(alpha);
            zz[l*(slices+1)+s]=r2*sin(beta);
            
        
            
            xx_normal[l*(slices+1)+s]=cos(beta)*cos(alpha);
            yy_normal[l*(slices+1)+s]=cos(beta)*sin(alpha);
            zz_normal[l*(slices+1)+s]=sin(beta);
            
            if (LG_Appearance::currentTexture) {
                ss_text[l*(slices+1)+s]=s_distFromStartOfLoop/s_lenght;
                tt_text[l*(slices+1)+s]=t_distFromStartOfLoop/t_lenght;
            }
            
            
            
            beta+=delta_beta;
        }
        
        
        alpha+=delta_apha;
    }
    
    
    
    for (int l=0; l<=loops; l++) {
        
        beta=0;
        for (int s=0; s<=slices; s++) {
            
            printf("texture[%d]=(%f,%f)\n",l*(slices+1)+s,ss_text[l*(slices+1)+s],tt_text[l*(slices+1)+s]);
            beta+=delta_beta;
        }
        alpha+=delta_apha;
    }

    
    
    

    

}