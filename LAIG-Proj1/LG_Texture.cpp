#include "LG_Texture.h"

#define LG_TEXTURE_ID_ "_LG_TEXTURE_"






#pragma mark - Constructors
LG_Texture::LG_Texture(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, getIdentifierFromElement(element))
{

    
    if (!str_eq(element->Value(), LG_TEXTURE_XML_TAG_NAME)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_TEXTURE_XML_TAG_NAME,element->Value());
    }

	string_tryToAttributeVariable(LG_TEXTURE_ATT_FILE, element, file);
	double_tryToAttributeVariable(LG_TEXTURE_ATT_TEXTLENGTH_S, element, texlength_s);
	double_tryToAttributeVariable(LG_TEXTURE_ATT_TEXTLENGTH_T, element, texlength_t);
}



LG_Texture::LG_Texture(LG_Node_Map *map,string file,double s,double t,string identifier):LG_Parsable_Node(map,identifier),texlength_s(s),texlength_t(t),file(file) {
    
    
}
#pragma mark - Helper Methods

string LG_Texture::getIdentifierFromElement(TiXmlElement *elem) {
    
    string theID;
    string_tryToAttributeVariable(LG_TEXTURE_ATT_ID, elem, theID);
    return theID;
    
}

#pragma mark - Destructor
LG_Texture::~LG_Texture()
{
}
