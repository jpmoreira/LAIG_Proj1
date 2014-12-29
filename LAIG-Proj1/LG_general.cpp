//
//  LG_general.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 17/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "LG_general.h"
#include <iostream>


const char * getDocumentName(int argc,char * argv[]){
    
    
    if (argc<2) {
        std::cout<<"No file name provided."<<std::endl;
		std::cout << "Will assume file with name: ../data/LAIG3_T4G05_2.xml " << std::endl;

		return "../data/LAIG3_T4G05_2.xml";
    }
    
    return argv[1];
    
    
    
    
}