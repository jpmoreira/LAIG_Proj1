//
//  LG_Board_Piece.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 22/12/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Board_Piece__
#define __LAIG_Proj1__LG_Board_Piece__

#include <stdio.h>

#include "LG_Primitive.h"
#include "LG_Texture.h"
#include "LG_Graph.h"


#define LG_Board_Piece_XML_Tag_Name_Tzaar "tzaar"
#define LG_Board_Piece_XML_Tag_Name_Tzarra "tzarra"
#define LG_Board_Piece_XML_Tag_Name_Tott "tott"

#define LG_Board_Piece_Color_XML_Attribute_Value_Black "black"
#define LG_Board_Piece_Color_XML_Attribute_Value_White "white"

#define LG_Board_Piece_ID "LG_Board_Piece_ID_"


typedef enum {

    Tzaar,
    Tzarra,
    Tott
    
    
} PieceType;

typedef enum {


    Black,
    White
    
} Color;








class LG_Board_Piece: public LG_Primitive {
    
    
private:
    
    PieceType type;
    Color color;
    
    
    
    /**
     *
     * Loads the content of the piece.
     *
     **/
    LG_Graph_Node * loadContents(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *textureMap,TiXmlElement *elem);
    
    
    /**
     *
     *Returns the name for the file containing the subtree stuff contained in this piece
     *
     **/
    inline string filenameForContent(){
        
#ifdef _WIN32
		return "../data/"+this->typeSpecifier() + "_" + this->colorSpecifier() + ".anfsnipset";
#endif

        return this->typeSpecifier()+"_"+this->colorSpecifier()+".anfsnipset";
        
    }

    /**
     *
     * Returns the color filename specifier for the color of this piece
     *
     **/
    inline string colorSpecifier(){
    
        if (this->color==White) return LG_Board_Piece_Color_XML_Attribute_Value_White;
        return LG_Board_Piece_Color_XML_Attribute_Value_Black;
    
    }
    
    /**
     *
     * Returns the type filename specifier for the color of this piece
     *
     **/
    inline string typeSpecifier(){
    
    
        if(this->type==Tzaar)return LG_Board_Piece_XML_Tag_Name_Tzaar;
        else if (this->type==Tzarra) return LG_Board_Piece_XML_Tag_Name_Tzarra;
        return LG_Board_Piece_XML_Tag_Name_Tott;
    }
    
    
    
   static inline string idForElement(TiXmlElement *elem){
       
       string a=LG_Board_Piece_ID;
        
        string b=elem->Value();
        return string (a+b);
        
       
        
   }
    

    LG_Board_Piece(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *textureMap,TiXmlElement *elem);
    
    
public:
    
    
  
    
    static LG_Board_Piece *pieceForElement(LG_Node_Map *map,LG_Node_Map *app_map,LG_Node_Map *textureMap,TiXmlElement *elem);
    
    virtual void calculateTextureCoordinates ();
    
    PieceType getType();
    
    Color getColor();
    
    virtual void draw();
};

#endif /* defined(__LAIG_Proj1__LG_Board_Piece__) */
