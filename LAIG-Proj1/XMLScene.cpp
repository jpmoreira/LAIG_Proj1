#include "XMLScene.h"
using std::string;


bool textToBool(char* text_bool, bool default_opt){
	if(!strcmp(text_bool, "true"))
		return true;
	if(!strcmp(text_bool, "false"))
		return false;

	return default_opt;
}

XMLScene::XMLScene(char *filename)
{

	// Read XML from file

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		exit( 1 );
	}

	TiXmlElement* rootElement= doc->FirstChildElement( "anf" );

	if (rootElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}

	globalsElement = rootElement->FirstChildElement( "globals" );
	camerasElement = rootElement->FirstChildElement( "cameras" );
	lightsElement =  rootElement->FirstChildElement( "lights" );
	texturesElement =  rootElement->FirstChildElement( "textures" );
	nodesElement =  rootElement->FirstChildElement( "Nodes" );
	appearancesElement = rootElement->FirstChildElement("appearances");
	graphElement =  rootElement->FirstChildElement( "graph" );



	if (globalsElement == NULL){
		printf("ERROR globals block not found!\n");
		exit(1);
	}
	else
	{
		printf("Processing globals:\n");
		if(!fillGlobalsElement(globalsElement))
			exit(2);
	}


	if(camerasElement == NULL){
		printf("ERROR cameras block not found!\n");
		exit(1);
	}
	else{
		printf("processing cameras\n");
		printf("%s\n", camerasElement->Attribute("initial"));

		if(!fillCamerasElement(camerasElement))
			exit(2);
	}

	if (lightsElement == NULL){
		printf("ERROR lights block not found!\n");
		exit(1);
	}
	else{
		printf("processing lights\n");

		if (!fillLightsElement(lightsElement))
			exit(2);
	}


	if (texturesElement == NULL){
		printf("ERROR textures block not found!\n");
		exit(1);
	} else{
		printf("processing textures\n");

		fillTexturesElement(texturesElement);
	}


	if (appearancesElement == NULL){
		printf("ERROR appearences block not found!\n");
		exit(1);
	}
	else{
		printf("processing appearences\n");
		
		if (!fillAppearencesElement(appearancesElement))
			exit(2);
	}


	// graph section
	if (graphElement == NULL)
		printf("Graph block not found!\n");
	else
	{
		//char *prefix="  -";
		TiXmlElement *node=graphElement->FirstChildElement();

		while (node)
		{
			printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
			TiXmlElement *child=node->FirstChildElement();
			while (child)
			{
				if (strcmp(child->Value(),"Node")==0)
				{
					// access node data by searching for its id in the nodes section

					TiXmlElement *noderef=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

					if (noderef)
					{
						// print id
						printf("  - Node id: '%s'\n", child->Attribute("id"));

						// prints some of the data
						printf("    - Material id: '%s' \n", noderef->FirstChildElement("material")->Attribute("id"));
						printf("    - Texture id: '%s' \n", noderef->FirstChildElement("texture")->Attribute("id"));

						// repeat for other leaf details
					}
					else
						printf("  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n", child->Attribute("id"));

				}
				if (strcmp(child->Value(),"Leaf")==0)
				{
					// access leaf data by searching for its id in the leaves section
					TiXmlElement *leaf=findChildByAttribute(rootElement,"id",child->Attribute("id"));

					if (leaf)
					{
						// it is a leaf and it is present in the leaves section
						printf("  - Leaf id: '%s' ; type: '%s'\n", child->Attribute("id"), leaf->Attribute("type"));

						// repeat for other leaf details
					}
					else
						printf("  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",child->Attribute("id"));
				}

				child=child->NextSiblingElement();
			}
			node=node->NextSiblingElement();
		}
	}

}

XMLScene::~XMLScene()
{
	delete(doc);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
	// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
	// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


//all elements must be found and attributes set
bool XMLScene::fillGlobalsElement(TiXmlElement *globalsElement){
	TiXmlElement* drawingElement=globalsElement->FirstChildElement("drawing");
	TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
	TiXmlElement* lightingElement=globalsElement->FirstChildElement("lighting");


	if (drawingElement)		//setting drawing element attributes
	{

		char * mode, *shading, *background;
		float r, g, b, a;

		mode=(char *) drawingElement->Attribute("mode");

		if(!strcmp(mode, "fill") || !strcmp(mode, "line") || !strcmp(mode, "point") )
			printf("globals::drawing::mode attr set\n");
		else{
			printf("ERROR globals::drawing::mode attr not set\n");
			return false;
		}


		shading=(char *) drawingElement->Attribute("shading");
		if(!strcmp(shading, "flat") || !strcmp(shading, "gouraud"))
			printf("globals::drawing::shading attr set\n");
		else{
			printf("ERROR globals::drawing::shading attr not set\n");
			return false;
		}


		background=(char *) drawingElement->Attribute("background");
		if(background && sscanf(background,"%f %f %f %f",&r, &g, &b, &a)==4)
			printf("globals::drawing::background attr set\n");
		else{
			printf("ERROR globals::drawing::background attr not set\n");
			return false;
		}

	}
	else{
		printf("ERROR globals::drawing element of globals was not found\n");
		return false;
	}



	if(cullingElement){ //setting culling element attributes
		char* face;
		char* order;

		face=(char *) cullingElement->Attribute("face");
		if(!strcmp(face, "none") || !strcmp(face, "back") || !strcmp(face, "front") || !strcmp(face, "both") )
			printf("globals::culling::face attr set\n");
		else{
			printf("ERROR globals::culling::face attr not set\n");
			return false;
		}

		order=(char *) cullingElement->Attribute("order");
		if(!strcmp(order, "cw") || !strcmp(order, "ccw"))
			printf("globals::culling::order attr set\n");
		else{
			printf("ERROR globals::culling::order attr not set\n");
			return false;
		}
	}
	else{
		printf("ERROR globals::culling elementwas not found\n");
		return false;
	}


	if(lightingElement){	//setting lightning element attributes
		bool doublesided, local, enabled;
		char * ambient;
		float r, g, b, a;
		char * text_bool;

		text_bool=(char *) lightingElement->Attribute("doublesided");
		doublesided = textToBool(text_bool, false);

		text_bool=(char *) lightingElement->Attribute("local");
		local = textToBool(text_bool, false);

		text_bool=(char *) lightingElement->Attribute("enabled");
		enabled = textToBool(text_bool, false);

		ambient=(char *) lightingElement->Attribute("ambient");
		if(ambient && sscanf(ambient,"%f %f %f %f",&r, &g, &b, &a)==4)
			printf("ambient attr set\n");
		else{
			printf("error: background attr not set\n");
			return false;
		}	
	}
	else{
		printf("ERROR globals::lightning element was not found\n");
		return false;
	}


	return true;
}


bool XMLScene::fillCamerasElement(TiXmlElement *camerasElement){
	TiXmlElement* perspectiveElement=camerasElement->FirstChildElement("perspective");
	TiXmlElement* orthoElement=camerasElement->FirstChildElement("ortho");

	char *initial=(char *) camerasElement->Attribute("initial");
	//char *initial=	strcpy(initial, camerasElement->Attribute("initial")); whaaat?!

	if(initial==NULL || initial == "")
		return false;

	bool at_leat_one = false; //at least one perspective or ortho element must exist and be valid
	bool initial_found = false; //the initial camera is found and correctly set

	//**processing perspective elements**
	do{
		if(!perspectiveElement)
			break;

		char *id, *pos, *target; 
		float near, far, angle, pos_x, pos_y, pos_z, target_x, target_y, target_z;

		//all attributes must be set to form a valid tag

		id=(char *) perspectiveElement->Attribute("id");
		if(id==NULL || id=="")	
			continue;

		//documentation found, but can't find implementation
		/*if(perspectiveElement->QueryStringAttribute("id", &id) != TIXML_SUCCESS);
		continue;*/

		if(perspectiveElement->QueryFloatAttribute("near", &near) != TIXML_SUCCESS ||
			perspectiveElement->QueryFloatAttribute("far", &far) != TIXML_SUCCESS ||
			perspectiveElement->QueryFloatAttribute("angle", &angle) != TIXML_SUCCESS)
			continue;	//one or more attributes not set

		pos=(char *) perspectiveElement->Attribute("pos");
		if(!(pos && sscanf(pos,"%f %f %f",&pos_x, &pos_y, &pos_z)==3))
			continue;

		target=(char *) perspectiveElement->Attribute("target");
		if(!(target && sscanf(target,"%f %f %f",&target_x, &target_y, &target_z)==3))
			continue;

		if(strcmp(initial, id) == 0)
			initial_found = true;

		//add camera here

		at_leat_one = true;	//all values were successfully set, valid tag

	}	while((perspectiveElement=perspectiveElement->NextSiblingElement("perspective"))); //repeat for every perspective tag


	//**processing ortho elements**
	do{
		if(!orthoElement) //for the firstchild
			break;


		char *id, *direction;
		float near, far, left, right, top, bottom;
		//all attributes must be set to form a valid tag


		//documentation found, but can't find implementation
		/*if(orthoElement->QueryStringAttribute("id", &id) != TIXML_SUCCESS);
		continue;*/
		id=(char *) orthoElement->Attribute("id");
		if(id==NULL || id=="")	
			continue;

		if(orthoElement->QueryFloatAttribute("near", &near) != TIXML_SUCCESS ||
			orthoElement->QueryFloatAttribute("far", &far) != TIXML_SUCCESS ||
			orthoElement->QueryFloatAttribute("left", &left) != TIXML_SUCCESS ||
			orthoElement->QueryFloatAttribute("right", &right) != TIXML_SUCCESS ||
			orthoElement->QueryFloatAttribute("top", &top) != TIXML_SUCCESS ||
			orthoElement->QueryFloatAttribute("bottom", &bottom) != TIXML_SUCCESS
			)
			continue;	//one of the elements was not correctly set

		direction =(char *) orthoElement->Attribute("direction");
		if(!(direction && (strcmp(direction, "x") == 0 || strcmp(direction, "y") == 0 || strcmp(direction, "z") == 0)))
			continue;

		if(strcmp(initial, id) == 0)
			initial_found = true;

		//add camera here

		at_leat_one= true;

	}	while ((orthoElement=orthoElement->NextSiblingElement("ortho")));


	return at_leat_one & initial_found;
}


bool XMLScene::fillLightsElement(TiXmlElement *lightsElement){
	TiXmlElement *lightElement = lightsElement->FirstChildElement("light");

	bool at_least_one=false;

	do
	{
		//variables of all lights
		char *id, *type, *pos;
		bool enabled, marker;
		float pos_x, pos_y, pos_z;

		//variables of a spot type light
		float angle, exponent, target_x, target_y, target_z;
		char *target;


		id = (char *) lightElement->Attribute("id");
		if(strcmp(id, "") == 0 || id == NULL)
			continue;

		type = (char *) lightElement->Attribute("type");

		if(strcmp(type, "spot")==0){
			//getting specific spot light attributes
			if(lightElement->QueryFloatAttribute("angle", &angle)!=TIXML_SUCCESS||
				lightElement->QueryFloatAttribute("exponent", &exponent) != TIXML_SUCCESS)
				continue;

			target=(char *) lightElement->Attribute("target");
			if(!(target && sscanf(target,"%f %f %f",&target_x, &target_y, &target_z)==3))
				continue;

		}	else if(!(strcmp(type, "omni")==0))	//if type != spot, then must be omni
			continue;

		//getting generic light attributes location enabled marker
		char *text_bool = (char *) lightElement->Attribute("enabled");
		if(text_bool)
			enabled = textToBool(text_bool, true);
		else
			continue;


		text_bool = (char *) lightElement->Attribute("marker");
		if(text_bool)
			marker = textToBool(text_bool, true);
		else
			continue;


		pos = (char *) lightElement->Attribute("pos");
		if(!(pos && sscanf(pos, "%f %f %f", &pos_x, &pos_y, &pos_z) == 3))
			continue;

		/*if(!fillLightComponents(lightElement))
		continue;*/

		//fill light components
		bool ambient= false, diffuse= false, specular= false; 
		TiXmlElement *lightComponent = lightElement->FirstChildElement("component");

		do
		{
			if(!lightComponent)
				break;

			char *component_type, *value;
			float r, g, b, a;

			value = (char *) lightComponent->Attribute("value");
			if(!(value && sscanf(value, "%f %f %f %f", &r, &g, &b, &a) ==4))
				continue;


			component_type = (char *) lightComponent->Attribute("type");
			if(strcmp(component_type, "ambient") == 0){
				ambient= true;
				//add component here
			}else if(strcmp(component_type, "diffuse") == 0){
				diffuse= true;
				//add component here
			}else if(strcmp(component_type, "specular") == 0){
				specular= true;
				//add component here
			}

		} while ((lightComponent = lightComponent->NextSiblingElement("component")));


		//save light according to type

		at_least_one = true;
	} while ((lightElement=lightElement->NextSiblingElement("light")));

	return at_least_one;
}


void XMLScene::fillTexturesElement(TiXmlElement *texturesElement){
	TiXmlElement *textureElement = texturesElement->FirstChildElement("texture");


	if(textureElement)
		do
		{
			//<texture id="ss" file="ss" texlength_s="ff" texlength_t="ff" />
			char *id, *file;
			float texlength_s, texlength_t;

			id = (char *) textureElement->Attribute("id");
			if(id== NULL || strcmp(id, "") == 0)
				continue;

			file = (char *) textureElement->Attribute("file");
			if(file== NULL || strcmp(file, "") == 0)
				continue;

			if (textureElement->QueryFloatAttribute("texlength_s", &texlength_s) != TIXML_SUCCESS ||
				textureElement->QueryFloatAttribute("texlength_t", &texlength_t) != TIXML_SUCCESS)
				continue;

			//save texture
			printf("texture created successfuly\n");

		} while ((textureElement= texturesElement->NextSiblingElement("texture")));
}


bool XMLScene::fillAppearencesElement(TiXmlElement *appearencesElement){
	bool at_least_one = false;

	TiXmlElement *appearanceElement = appearancesElement->FirstChildElement("appearance");

	if(appearanceElement)
		do
		{
			char *id, *textureref;
			bool textureref_associated = false, ambient= false,
				diffuse= false, specular = false;
			float shininess;


			id = (char *) appearanceElement->Attribute("id");
			if(id==NULL || strcmp(id, "")== 0)
				continue;

			textureref = (char *) appearanceElement->Attribute("textureref");
			if(!(textureref==NULL || strcmp(textureref, "")== 0))
				textureref_associated = true;

			if((appearanceElement->QueryFloatAttribute("shininess", &shininess))!=TIXML_SUCCESS)
				continue;

			//components
			char *type, *value;
			float r,g,b,a;

			TiXmlElement *appearenceComponent = appearanceElement->FirstChildElement("component");

			if(!appearenceComponent)
				continue;
			do
			{

				value = (char *) appearenceComponent->Attribute("value");
				if(!(value && sscanf(value, "%f %f %f %f", &r, &g, &b, &a) ==4))
					continue;

				type = (char *) appearenceComponent->Attribute("type");
				if(strcmp(type, "diffuse")==0)
				{
					diffuse=true;
					//add component
				} else if (strcmp(type, "ambient")==0)
				{
					ambient=true;
					//add component
				} else if (strcmp(type, "specular")==0)
				{
					specular=true;
					//add component
				}

			} while ((appearenceComponent= appearenceComponent->NextSiblingElement("component")));



			at_least_one=true;
		} while ((appearanceElement=appearancesElement->NextSiblingElement("appearance")));

		return at_least_one;
}