#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#define private public//here for testing purposes basicaly disables incapsulation for the files included after
#include "LG_Node.h"



unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Test child operations" ) {
    
    LG_Node_Map *theMap=new LG_Node_Map();

    


    LG_Node *root=new LG_Node(theMap,"rootID");
    
    string theRootID="rootID";
    
    SECTION("Verify addition to map"){
    
    
        
        
        auto it=theMap->find(theRootID);
        
        if (it==theMap->end()) FAIL("Not Found");
        
        REQUIRE(it->second==root);
    
    }
    
    SECTION("Verify Child additions"){
    
    
        LG_Node * child=new LG_Node(theMap,"child");
        
        root->addChild(child);
        
        LG_Node *supposedChild=root->child(0);
        
        REQUIRE(supposedChild==child);
        
    }
    
    
    SECTION("Accessing Illegal child"){
    
        
        
        LG_Node * child=new LG_Node(theMap,"child");
        
        root->addChild(child);
        
        LG_Node *supposedChild=root->child(1);
        
        REQUIRE(supposedChild==NULL);
    
    
    }
    

    
    
    
    
    
    
    
    
    
    
}
