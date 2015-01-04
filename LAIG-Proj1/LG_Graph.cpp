//
//  LG_Graph.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 01/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_Graph.h"


#define LG_Graph_Identifier "_LG_Graph_ID"

#define LG_Graph_Root_XML_Att_Name "rootid"



#pragma mark - Constructor




LG_Graph::LG_Graph(LG_Node_Map *appearancesMap, LG_Node_Map *animationsMap, TiXmlElement *elem, LG_Node_Map *theMap, bool verifyReferences) :LG_Node(NULL, LG_Graph_Identifier), appearancesMap(appearancesMap), animationsMap(animationsMap){


	map = theMap;


	if (!str_eq(LG_Graph_XML_Tag_Name, elem->Value())) {
		throw new LG_Parse_Exception_Wrong_Element_Name(LG_Graph_XML_Tag_Name, elem->Value());
	}


	TiXmlElement *childElement = elem->FirstChildElement();

	while (childElement) {



		if (str_eq(LG_Graph_Node_XML_Tag_Name, childElement->Value()))
			new LG_Graph_Node(map, appearancesMap, animationsMap, childElement, false);//create node and add it to mapForNodes
		else
			if (str_eq(LG_Button_XML_Tag_Name, childElement->Value()))
				new LG_Button(map, appearancesMap, animationsMap, childElement);


		LG_Node *debug;
		auto it = map->find("levelExpert");
		if (it != map->end())
			debug = it->second;

		childElement = childElement->NextSiblingElement();
	}


	handleRootNode(elem);

	if (verifyReferences)
		verifyNodeReferences(elem);







}



#pragma mark - Helper Methods




void LG_Graph::handleRootNode(TiXmlElement *graphElement){


	string rootID;


	LG_Parsable_Node::string_tryToAttributeVariable(LG_Graph_Root_XML_Att_Name, graphElement, rootID);


	auto it = map->find(rootID);
	if (it == map->end()) {

		throw new LG_Parse_Exception_Broken_Reference(LG_Graph_XML_Tag_Name, rootID.c_str(), LG_Graph_Node_XML_Tag_Name);
	}

	root = (LG_Graph_Node *)it->second;
	addChild(root);

}


void LG_Graph::verifyNodeReferences(TiXmlElement *graphElement){


	//for each node
	for (LG_Node_Map::iterator it = map->begin(); it != map->end(); it++) {

		LG_Node *node = (LG_Node *)it->second;
		LG_ID_Vector &childsIDs = node->childsIDs;

		for (unsigned int i = 0; i < childsIDs.size(); i++) {//for each child in this node

			auto it2 = map->find(childsIDs[i]);

			if (it2 == map->end()) {
				throw new LG_Parse_Exception_Broken_Reference(it->second->identifier.c_str(), childsIDs[i].c_str(), LG_Graph_Node_XML_Tag_Name);
			}
		}




	}



}


#pragma mark - Drawing


void LG_Graph::draw(bool selecMode){


	root->draw(selecMode);

}


#pragma mark - Configuration


void LG_Graph::config(){

	root->config();

}

void LG_Graph::update(unsigned long time){


	root->update(time);
}


#pragma mark - Picking

LG_Node * LG_Graph::nodeWithPickingID(unsigned int identif){

	return this->root->nodeWithPickingID(identif);

}


#pragma mark - Finding Node

LG_Node * LG_Graph::nodeWithID(string identif){


    auto it=this->root->map->find(identif);
    
    if (it==this->root->map->end())return NULL;
    return it->second;
}

LG_Graph::~LG_Graph(){
    
    for(auto pair:*map)delete pair.second;

}
