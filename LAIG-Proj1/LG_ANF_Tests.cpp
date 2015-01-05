#ifdef _WIN32
//#define _WINSOCKAPI_    // stops windows.h including winsock.h
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <CGFapplication.h>
#include <iostream>
#include <string>
#include "LG_ANF.h"
#include "LG_Scene.h"
#include "LG_general.h"
#include "LG_Flag.h"

#include "LG_Tzaar.h"

int main(int argc, char * argv[]){

    
    
    CGFapplication app = CGFapplication();
    
    int result=0;
    
    try {
        app.init(&argc, argv);
        
        //LG_Scene *scene=new LG_Scene();
        LG_Tzaar tzaar_scene;
        LG_Tzaar::currentTzaar=&tzaar_scene;
        
        //LG_Tzaar *tzaar_scene=LG_Tzaar::getCurrentTzaar();
		//LG_SceneInterface *scene_interface = new LG_SceneInterface();


    
        vector<string> fileNames=getDocumentNames(argc, argv);

        tzaar_scene.setDocNameForScene(fileNames[0]);
        tzaar_scene.setDocNameForMenu(fileNames[1]);
        tzaar_scene.setDocNameForShortMenu(fileNames[2]);
        
        
        app.setScene(&tzaar_scene);
        
        
        app.setInterface(&tzaar_scene);
        
        app.run();
    }
    catch(GLexception& ex) {
       cout << "Erro: " << ex.what();
        return -1;
    }
    catch(LG_Parse_Exception *ex){
        
        cout<< "####### Parsing Error: #######"<<endl;
        
        cout<< ex->what()<<endl;
        
        cout<< "##############"<<endl;
        
    }
    catch(exception& ex) {
        cout << "Erro inesperado: " << ex.what();
        return -1;
    }
    
    
    
    return result;

}
