#include "LG_Lighting.h"

#define LG_Lighting_ElementName "lighting";


#pragma mark - Constructors


LG_Lighting::LG_Lighting(LG_Node_Map *map,TiXmlNode *node):LG_Parsable_Node(map,LG_Lighting_Node_ID),doublesided(false),local(true),enabled(true){
    
    

    enum TiXmlNode::NodeType type=(enum TiXmlNode::NodeType )node->Type();
    
//#warning Do verifications here
    
}


#pragma mark - Element Parsing Methods


void LG_Lighting::verifyElementName(TiXmlElement *element){


    


}

void LG_Lighting::verifyAttributesAndValues(TiXmlElement *element){
    
    TiXmlAttribute *att=element->FirstAttribute();
    
    
    


}