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
LG_Graph::LG_Graph(LG_Node_Map *appearancesMap,TiXmlElement *elem):LG_Node(NULL,LG_Graph_Identifier),appearancesMap(appearancesMap){
    
    map=new LG_Node_Map();//initialized after not in super constructor so that we dont get added to the map
    
    if (!str_eq(LG_Graph_XML_Tag_Name, elem->Value())) {
        throw new LG_Parse_Exception_Wrong_Element_Name(LG_Graph_XML_Tag_Name,elem->Value());
    }
    
    
    TiXmlElement *childElement=elem->FirstChildElement();
    
    while (childElement) {
        
       
    
        new LG_Graph_Node(map,appearancesMap,childElement);//create node and add it to mapForNodes
        
        
        childElement=childElement->NextSiblingElement();
    }
    
    
    handleRootNode(elem);
    
    verifyNodeReferences(elem);
    
    
    

    


}




#pragma mark - Helper Methods




void LG_Graph::handleRootNode(TiXmlElement *graphElement){
    
    
    string rootID;
    
    
    LG_Parsable_Node::string_tryToAttributeVariable(LG_Graph_Root_XML_Att_Name, graphElement, rootID);
    
    
    auto it=map->find(rootID);
    if (it==map->end()) {
        
        throw new LG_Parse_Exception_Broken_Reference(LG_Graph_XML_Tag_Name, rootID.c_str(), LG_Graph_Node_XML_Tag_Name);
    }
    
    root=(LG_Graph_Node *)it->second;
    addChild(root);

}


void LG_Graph::verifyNodeReferences(TiXmlElement *graphElement){


    //for each node
    for(LG_Node_Map::iterator it = map->begin(); it != map->end(); it++) {
        
        LG_Node *node=(LG_Node *)it->second;
        LG_ID_Vector &childsIDs=node->childsIDs;
        
        for (unsigned int i=0; i<childsIDs.size(); i++) {//for each child in this node
            
            auto it2=map->find(childsIDs[i]);
            
            if (it2==map->end()) {
                throw new LG_Parse_Exception_Broken_Reference(it->second->identifier.c_str(), childsIDs[i].c_str(), LG_Graph_Node_XML_Tag_Name);
            }
        }
        

        
        
    }
    


}


#pragma mark - Drawing


void LG_Graph::draw(){


    root->draw();

}

