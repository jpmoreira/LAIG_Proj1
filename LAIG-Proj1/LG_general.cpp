//
//  LG_general.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 17/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_general.h"
#include <iostream>


using std::string;
using std::vector;


const vector<string> getDocumentNames(int argc,char * argv[]){
    
    
    vector<string> vect;

    if (argc>=2) vect.push_back(string(argv[1]));
    else{
        std::cout<<"No file name provided for scene."<<std::endl;
        std::cout << "Will assume file with name: ../data/scene.xml " << std::endl;
        vect.push_back(string("../data/scene.xml"));
    }
    
    if(argc>=3)vect.push_back(string(argv[2]));
    else{
        std::cout<<"No file name provided for menu."<<std::endl;
        std::cout << "Will assume file with name: ../data/menu.xml " << std::endl;
        vect.push_back(string("../data/menu.xml"));
    }
    
    if(argc>=4)vect.push_back(string(argv[3]));
    else{
        std::cout<<"No file name provided for short menu."<<std::endl;
        std::cout << "Will assume file with name: ../data/short_menu.xml " << std::endl;
        vect.push_back(string("../data/short_menu.xml"));
    }
    
    
    return vect;
    
    
    
    
}