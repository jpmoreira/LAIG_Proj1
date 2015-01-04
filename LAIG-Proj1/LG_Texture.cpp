#include "LG_Texture.h"

#define LG_TEXTURE_ID_ "_LG_TEXTURE_"






#pragma mark - Constructors
LG_Texture::LG_Texture(LG_Node_Map *map, TiXmlElement *element) :LG_Parsable_Node(map, getIdentifierFromElement(element),NULL)
{

    
    if (!str_eq(element->Value(), LG_TEXTURE_XML_TAG_NAME)) {
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_TEXTURE_XML_TAG_NAME,element->Value());
    }
    
    

	string_tryToAttributeVariable(LG_TEXTURE_ATT_FILE, element, file);
	double_tryToAttributeVariable(LG_TEXTURE_ATT_TEXTLENGTH_S, element, texlength_s);
	double_tryToAttributeVariable(LG_TEXTURE_ATT_TEXTLENGTH_T, element, texlength_t);
    
    configTexture();
    
    
}



LG_Texture::LG_Texture(LG_Node_Map *map,string file,double s,double t,string identifier):LG_Parsable_Node(map,identifier,NULL),texlength_s(s),texlength_t(t),file(file) {
    
    
    configTexture();
    
    
}
#pragma mark - Helper Methods

string LG_Texture::getIdentifierFromElement(TiXmlElement *elem) {
    
    string theID;
    string_tryToAttributeVariable(LG_TEXTURE_ATT_ID, elem, theID);
    return theID;
    
}


void LG_Texture::configTexture() {
    
    try {
        loadTexture(file);
    } catch (exception *x) {
        printf("Unable to load texture from file %s\n",file.c_str());
    }
    
    
}

#pragma mark - Destructor
LG_Texture::~LG_Texture()
{
}


#pragma mark - Getters & Setters


double LG_Texture::getLength_s(){

    return texlength_s;
}


double LG_Texture::getLength_t(){
    
    return texlength_t;

}


#pragma mark - Texture Application


void LG_Texture::apply() {

    glEnable(GL_TEXTURE_2D);
    CGFtexture::apply();
    //glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    
}



void LG_Texture::unapply(){
    
    
    glBindTexture(GL_TEXTURE_2D, NULL);//unapply
    glDisable(GL_TEXTURE_2D);


}