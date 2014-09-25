#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#define DEBUG 1

#include "tinyxml.h"
#include <string>

class XMLScene
{
public:
	XMLScene(char *filename);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
	/*sets the globals elements and its attributes. Returns true if all elements and their attributes are correctly set, false otherwise*/
	bool fillGlobalsElement(TiXmlElement* globalsElement);	
	bool fillCamerasElement(TiXmlElement* CamerasElement);
	bool fillLightsElement(TiXmlElement* LightsElement);
	void fillTexturesElement(TiXmlElement* texturesElement);
	bool fillAppearencesElement(TiXmlElement* appearencesElement);
	bool fillNodesElement(TiXmlElement* nodesElement);
	bool fillGraphElement(TiXmlElement* graphElement);

	bool fillLightComponents(TiXmlElement* lightElement);


protected:

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement;
	TiXmlElement* lightsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;
	TiXmlElement* nodesElement;




};

#endif