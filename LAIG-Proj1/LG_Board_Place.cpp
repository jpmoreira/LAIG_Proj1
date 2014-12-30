//
//  LG_Board_Place.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Board_Place.h"


#define LG_Board_Place_Nr_Pieces_XML_Att_Name "pieces"





LG_Board_Place::LG_Board_Place(LG_Node_Map *map,LG_Node_Map *app_map, LG_Node_Map *text_Map,TiXmlElement *element):LG_Primitive(map,idForElement(element)){
    
    selectable=true;//board places are selectable
    
    evalElemName(LG_Board_Place_XML_Tag_Name, element->Value());
    
    positiveInt_tryToAttributeVariable(LG_Board_Place_X_XML_Att_Name, element, x);
    positiveInt_tryToAttributeVariable(LG_Board_Place_Y_XML_Att_Name, element, y);
    
    TiXmlElement *childElement=element->FirstChildElement();
    
    
    if (childElement) {
        this->piece=LG_Board_Piece::pieceForElement(map, app_map, text_Map, childElement);
    }
    else{
        this->piece=NULL;
        nrPieces=0;
    }
    
    if(piece){
    
    
        try {
            positiveInt_tryToAttributeVariable(LG_Board_Place_Nr_Pieces_XML_Att_Name, element, nrPieces);
        } catch (LG_Parse_Exception_Missing_Attribute *ex) {//if attribute not found assume 1
            nrPieces=1;
        }
    
    
    }
    
    //LG_Bounce_Animation *anim=new LG_Bounce_Animation(map);
    //this->animations.push_back( new LG_AnimationState(map, anim, this));
    


}
LG_Board_Place::LG_Board_Place(LG_Node_Map *map,LG_Node_Map *app_map, LG_Node_Map *text_Map,int x, int y,int nrPieces, LG_Board_Piece *piece):LG_Primitive(map,idForElement(x,y)),y(y),x(x),nrPieces(nrPieces),piece(piece){


    
}




void LG_Board_Place::stack(LG_Board_Piece *piece,int stackNr){
    
    if (piece==NULL && this->piece==NULL)return;
    
    if (piece==NULL || this->piece->getType()!=piece->getType() || this->piece->getColor()!= piece->getColor()) {
        this->piece=piece;
        nrPieces=stackNr;
    }
    
    else{
    
        nrPieces+=stackNr;
    }


}


void LG_Board_Place::stackFrom(LG_Board_Place *originalPlace){
    
    this->stack(originalPlace->piece,originalPlace->nrPieces);
    originalPlace->stack(NULL,0);

}


void LG_Board_Place::calculateTextureCoordinates(){
    
    
}

void LG_Board_Place::drawChilds(bool selectMode){

    for (int i=0; i<nrPieces; i++) {
        
        piece->draw(selectMode);
        glTranslated(0, 0.5, 0);
        
    }

}

void LG_Board_Place::setSelected(bool selected){
    
    LG_Node::setSelected(selected);
    if (selected) {
        LG_Bounce_Animation *anim=new LG_Bounce_Animation(map);
        this->animations.push_back( new LG_AnimationState(map, anim, this));
    }
    else{
        this->animations.pop_back();
    }
    
    
}


