//
//  LG_All_Tests.cpp
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 29/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#define LG_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#define private public //disable encapsulation for following files, allowing testing to be done
#define protected public
#include "catch.h"

#include "LG_Nodes_Tests.cpp"
#include "LG_Triangle_Tests.cpp"
