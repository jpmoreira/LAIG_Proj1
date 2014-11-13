#include <CGFapplication.h>
#include <iostream>
#include <string>
#include "LG_ANF.h"
#include "LG_Scene.h"
#include "LG_SceneInterface.h"
#include "LG_general.h"
#include "LG_Flag.h"

int main(int argc, char * argv[]){

    
    
    CGFapplication app = CGFapplication();
    
    int result=0;
    
    try {
        app.init(&argc, argv);
        
        LG_Scene *scene=new LG_Scene();
		LG_SceneInterface *scene_interface = new LG_SceneInterface();



#ifdef _WIN32
        scene->setDocName(getDocumentName(argc, argv));
#else
        scene->setDocName(getDocumentName(argc, argv));
#endif
        
        
        app.setScene(scene);
		scene_interface->setLightsContainer(scene);
		scene_interface->setCamerasContainer(scene);
		scene_interface->setDrawing(scene);
		scene_interface->setWind_var(LG_Flag::getWind());
        app.setInterface(scene_interface);
        
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
