//
//  LG_Board_Place.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Board_Place__
#define __LAIG_Proj1__LG_Board_Place__

#include <stdio.h>
#include "LG_Primitive.h"
#include "LG_Board_Piece.h"


#define LG_Board_Place_XML_Tag_Name "place"
#define LG_Board_Place_ID_Prefix "LG_Board_Place_"
#define LG_Board_Place_X_XML_Att_Name "x"
#define LG_Board_Place_Y_XML_Att_Name "y"

class LG_Board_Place: public LG_Primitive {
    
    
private:
    
    
    int x,y;
    int nrPieces;
    
    
    static inline string idForElement(TiXmlElement *elem){
    
    
        int x,y;
    
        positiveInt_tryToAttributeVariable(LG_Board_Place_X_XML_Att_Name, elem, x);
        positiveInt_tryToAttributeVariable(LG_Board_Place_Y_XML_Att_Name, elem, y);

        
        return idForElement(x,y);
           
    }
    
    static inline string idForElement(int x, int y){
    
        
        string a=string(LG_Board_Place_ID_Prefix);
        char buffer[50];
        
        sprintf(buffer, "%d_%d",x,y);
        
        return string(a+buffer);
    
    }
    
public:
    
    LG_Board_Piece *piece;
    
    
    void calculateTextureCoordinates();
    
    void stack(LG_Board_Piece *piece=NULL,int stackNr=1);
    
    void stackFrom(LG_Board_Place *originalPlace);
    
    
    LG_Board_Place(LG_Node_Map *map,LG_Node_Map *app_map, LG_Node_Map *text_Map,TiXmlElement *element);
    LG_Board_Place(LG_Node_Map *map,LG_Node_Map *app_map, LG_Node_Map *text_Map,int x, int y,int nrPieces, LG_Board_Piece *piece);
    
    virtual void drawChilds(bool selectMode);
    
    void setSelected(bool selected);
    
    void animationFinished(LG_AnimationState *state);
    
};

#endif /* defined(__LAIG_Proj1__LG_Board_Place__) */

