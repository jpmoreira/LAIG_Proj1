#include "LG_Texture.h"

#define _LG_Primitive_Name LG_TEXTURE_ID_
#define LG_TEXTURE_ID_ "_LG_TEXTURE_"

int LG_Texture::_LG_classIDNr = 0;





LG_Texture::LG_Texture(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, autoIdentifier)
{
	/*
		string id, file;
	double texlength_s, texlength_t;
	*/

	string_tryToAttributeVariable(LG_TEXTURE_ATT_ID, element, id);
	string_tryToAttributeVariable(LG_TEXTURE_ATT_FILE, element, file);
	double_tryToAttributeVariable(LG_TEXTURE_ATT_TEXTLENGTH_S, element, texlength_s);
	double_tryToAttributeVariable(LG_TEXTURE_ATT_TEXTLENGTH_T, element, texlength_t);
}


LG_Texture::~LG_Texture()
{
}
