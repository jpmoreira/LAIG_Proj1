//
//  LG_Board_Piece.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Board_Piece.h"
#include "LG_Appearance.h"
#include "LG_Texture.h"
#include "LG_Graph.h"






LG_Board_Piece * LG_Board_Piece::pieceForElement(LG_Node_Map *map, LG_Node_Map *app_map, LG_Node_Map *textureMap, TiXmlElement *elem){
    
    
    string identifier=idForElement(elem);
    
    
    auto it=map->find(identifier);
    if(it!=map->end()){
        return dynamic_cast<LG_Board_Piece *>(it->second);
    }
    
    
    LG_Board_Piece *piece=new LG_Board_Piece(map,app_map,textureMap,elem);
    return piece;
    
    

}

LG_Board_Piece * LG_Board_Piece::pieceForElement(LG_Node_Map *map, LG_Node_Map *app_map, LG_Node_Map *textureMap, Color color, PieceType type){
    
    
    string identifier=idForPiece(color, type);
    
    
    auto it=map->find(identifier);
    if(it!=map->end()){
        return dynamic_cast<LG_Board_Piece *>(it->second);
    }
    
    
    LG_Board_Piece *piece=new LG_Board_Piece(map,app_map,textureMap,color,type);
    return piece;
    
    
    
}

LG_Board_Piece::LG_Board_Piece(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *textureMap,Color color,PieceType type):LG_Primitive(map,idForPiece(color, type)){
    
    
    
    this->type=type;
    
    this->color=color;
    
    LG_Graph_Node *root=loadContents(map,app_map,textureMap);
    
    this->addChild(root);
    
    
    
    
}

LG_Board_Piece::LG_Board_Piece(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *textureMap,TiXmlElement *elem):LG_Primitive(map,idForElement(elem)){

    
    
    //try any hipotisys for the name, if none succedeeds than exception is actually thrown
    try {
        evalElemName(LG_Board_Piece_XML_Tag_Name_Tzarra, elem->Value());
        this->type=Tzarra;
    } catch (LG_Parse_Exception_Wrong_Element_Name *e) {
        
        try {
            
            evalElemName(LG_Board_Piece_XML_Tag_Name_Tott, elem->Value());
            this->type=Tott;
            
        } catch (LG_Parse_Exception_Wrong_Element_Name *e) {
        

            evalElemName(LG_Board_Piece_XML_Tag_Name_Tzaar, elem->Value());
            this->type=Tzaar;
            
        }
        
    }
    
    
    vector<string> possibleValues;
    possibleValues.push_back(string(LG_Board_Piece_Color_XML_Attribute_Value_Black));
    possibleValues.push_back(string(LG_Board_Piece_Color_XML_Attribute_Value_White));
    int save;
    enum_tryToAttribute(LG_Board_Piece_XML_Color_Attribute_Name, elem, save, &possibleValues);
    
    this->color=(Color)save;
    
    LG_Graph_Node *root=loadContents(map,app_map,textureMap);
    
    this->addChild(root);
    
    
    

    
    
    
    
    

    //handle color and place primitives
    
    
    
    
    
}

#pragma mark - Loading



LG_Graph_Node * LG_Board_Piece::loadContents(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *textureMap){
    
    
    string fileForContent=this->filenameForContent();
    
    
    
    
    TiXmlDocument *doc = new TiXmlDocument(fileForContent.c_str());
    
    bool couldLoad=doc->LoadFile();
    
    if(!couldLoad){
        
        string s;
        if (this->type==Tzaar) s=LG_Board_Piece_XML_Tag_Name_Tzaar;
        else if(this->type==Tzarra) s= LG_Board_Piece_XML_Tag_Name_Tzarra;
        else s= LG_Board_Piece_XML_Tag_Name_Tott;
        
        throw new LG_Parse_Exception_Unable_Load_Snipset(&s,&fileForContent);
    
    }
    
    

    TiXmlElement *element = doc->FirstChildElement(LG_TEXTURE_XML_TAG_NAME);
    
    while (element) {//Load Textures
    
        new LG_Texture(textureMap, element);
        
        element=element->NextSiblingElement(LG_TEXTURE_XML_TAG_NAME);
        
    }
    
    
    element=doc->FirstChildElement(LG_Appearance_XML_Tag_Name);
    
    
    while (element) {//Load Appearances
        
        new LG_Appearance(app_map,element,textureMap);
        
        element=element->NextSiblingElement(LG_Appearance_XML_Tag_Name);
    }
    
    
    element=doc->FirstChildElement(LG_Graph_XML_Tag_Name);
    
    LG_Graph *graph;
    
    if(element){
        
        graph=new LG_Graph(app_map,NULL,element,map, false);
        
    }
    
    
    else throw new LG_Parse_Exception_Missing_Element(LG_Graph_XML_Tag_Name);

    
    
    
    return graph->root;

    
    
    
    
    

    


}


void LG_Board_Piece::calculateTextureCoordinates(){
    
}



void LG_Board_Piece::draw(bool selectMode){

    //if (selectMode)return;
    
    LG_Node::draw(selectMode);

    //selectMode=true;
    //this->child(0)->draw();

}

#pragma mark - Getters & Setters


PieceType LG_Board_Piece::getType(){


    return this->type;
}



Color LG_Board_Piece::getColor(){
    
    
    return this->color;
}

