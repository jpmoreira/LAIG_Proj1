//
//  LG_Appearance.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//


#include "LG_Parsable_Node.h"
#include "LG_Appearance.h"



#define LG_Appearance_Shininess_XML_Att_Name "shininess"
#define LG_Apperance_Component_XML_Tag_Name "component"
#define LG_Apperance_Component_Type_XML_Att_Name "type"
#define LG_Apperance_Component_Value_XML_Att_Name "value"
#define LG_Apperance_Component_Type_Ambient_String "ambient"
#define LG_Apperance_Component_Type_Diffuse_String "diffuse"
#define LG_Apperance_Component_Type_Specular_String "specular"
#define LG_Apperance_Component_TextureRef_XML_Att_Name "textureref"

#pragma mark - Constructors


LG_Texture * LG_Appearance::currentTexture = NULL;

LG_Appearance::LG_Appearance(LG_Node_Map *map, TiXmlElement *elem, LG_Node_Map *texturesMap) :LG_Parsable_Node(map, getIdentifier(elem)), texture(NULL){

	initializeComponents();
	if (!str_eq(LG_Appearance_XML_Tag_Name, elem->Value())) {
		throw new LG_Parse_Exception_Wrong_Element_Name(LG_Appearance_XML_Tag_Name, elem->Value());
	}

	float_tryToAttributeVariable(LG_Appearance_Shininess_XML_Att_Name, elem, shininess);


	TiXmlElement *subElement = elem->FirstChildElement();

	while (subElement) {


		if (str_eq(subElement->Value(), LG_Apperance_Component_XML_Tag_Name)) {
			handleComponent(subElement);
		}

		subElement = subElement->NextSiblingElement();
	}


	try {
		handleTextureRef(texturesMap, elem);
	}
	catch (LG_Parse_Exception_Missing_Attribute *ex) {}//this attribute is not required

}

LG_Appearance::LG_Appearance(LG_Node_Map *map, LG_LightArray_f amb, LG_LightArray_f diff, LG_LightArray_f spec, float s, string identif, LG_Texture *texture) :LG_Parsable_Node(map, identif), shininess(s), texture(NULL){

	copyLightArrays_f(amb, ambient);
	copyLightArrays_f(diff, diffuse);
	copyLightArrays_f(spec, specular);
	this->texture = texture;


}


#pragma mark - Helper Methods

string LG_Appearance::getIdentifier(TiXmlElement *elem){


	string id;

	string_tryToAttributeVariable(LG_Appearance_ID_XML_Att_Name, elem, id);

	return id;

}


void LG_Appearance::handleComponent(TiXmlElement *component){

	string type;
	string_tryToAttributeVariable(LG_Apperance_Component_Type_XML_Att_Name, component, type);


	if (str_eq(type.c_str(), LG_Apperance_Component_Type_Ambient_String)) {

		lightArray_f_tryToAttributeVariable(LG_Apperance_Component_Value_XML_Att_Name, component, ambient);
	}

	else if (str_eq(type.c_str(), LG_Apperance_Component_Type_Diffuse_String)) {

		lightArray_f_tryToAttributeVariable(LG_Apperance_Component_Value_XML_Att_Name, component, diffuse);
	}
	else if (str_eq(type.c_str(), LG_Apperance_Component_Type_Specular_String)) {

		lightArray_f_tryToAttributeVariable(LG_Apperance_Component_Value_XML_Att_Name, component, specular);
	}
	else {
		vector<string> *possibleValue = new vector<string>();
		possibleValue->push_back(string(LG_Apperance_Component_Type_Ambient_String));
		possibleValue->push_back(string(LG_Apperance_Component_Type_Diffuse_String));
		possibleValue->push_back(string(LG_Apperance_Component_Type_Specular_String));

		throw new LG_Parse_Exception_Wrong_Attribute_Value(
			new string(component->Value()),
			new string(LG_Apperance_Component_Type_XML_Att_Name),
			new string(type), possibleValue);

	}

}


void LG_Appearance::initializeComponents(){

	shininess = LG_INVALID_DOUBLE;
	for (int i = 0; i < LG_LightArray_Lenght; i++) {
		ambient[i] = LG_INVALID_DOUBLE;
		diffuse[i] = LG_INVALID_DOUBLE;
		specular[i] = LG_INVALID_DOUBLE;

	}

}



void LG_Appearance::handleTextureRef(LG_Node_Map *texturesMap, TiXmlElement *element) {

	string textureRef;

	string_tryToAttributeVariable(LG_Apperance_Component_TextureRef_XML_Att_Name, element, textureRef);


	auto it = texturesMap->find(textureRef);

	if (it == texturesMap->end()) {

		throw new LG_Parse_Exception_Broken_Reference(new string(this->identifier), new string(textureRef), new string(LG_TEXTURE_XML_TAG_NAME));

	}

	texture = (LG_Texture *)it->second;



}



#pragma mark - Application




void LG_Appearance::apply() {


	_savedCurrentTexture = currentTexture;

	if (texture){
		texture->apply();
		currentTexture = texture;
	}
	glGetMaterialfv(GL_FRONT, GL_SHININESS, &_savedShininess);
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&_savedSpecular);
	glGetMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&_savedAmbient);
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&_savedDiffuse);





	if (shininess != LG_INVALID_FLOAT)glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	if (specular[0] != LG_INVALID_FLOAT)glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	if (ambient[0] != LG_INVALID_FLOAT)glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	if (diffuse[0] != LG_INVALID_FLOAT)glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);




}


void LG_Appearance::unapply(){


	//restore old defaults


	if (texture)texture->unapply();

	if (shininess != LG_INVALID_FLOAT)glMaterialf(GL_FRONT, GL_SHININESS, _savedShininess);
	if (specular[0] != LG_INVALID_FLOAT)glMaterialfv(GL_FRONT, GL_SPECULAR, _savedSpecular);
	if (ambient[0] != LG_INVALID_FLOAT)glMaterialfv(GL_FRONT, GL_AMBIENT, _savedAmbient);
	if (diffuse[0] != LG_INVALID_FLOAT)glMaterialfv(GL_FRONT, GL_DIFFUSE, _savedDiffuse);


	currentTexture = _savedCurrentTexture;

	if (currentTexture) currentTexture->apply();






}


#pragma mark - Getters & Setters


LG_Texture * LG_Appearance::getTexture() {

	return texture;
}


LG_Texture * LG_Appearance::getCurrentText(){
	return currentTexture;
}


