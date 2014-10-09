#pragma once
#include "LG_Parsable_Node.h"




#define LG_TEXTURE_ID "_LG_Light_Spot_"
#define LG_TEXTURE_ATT_ID "id"
#define LG_TEXTURE_ATT_FILE "file"
#define LG_TEXTURE_ATT_TEXTLENGTH_S "texlength_s"
#define LG_TEXTURE_ATT_TEXTLENGTH_T "texlength_t"
#define LG_TEXTURE_XML_TAG_NAME "texture"


class LG_Texture :
	public LG_Parsable_Node
{
public:
	LG_Texture(LG_Node_Map *map, TiXmlElement *element);
	~LG_Texture();


private:
	string file;
	double texlength_s, texlength_t;
    
    /**
     
     A method for getting the identifier from the texture.
     
     
     */
    string getIdentifierFromElement (TiXmlElement *elem);

};

