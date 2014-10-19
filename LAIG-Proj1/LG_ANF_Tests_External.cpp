
#include <CGFapplication.h>
#include <iostream>
#include <string>
#include "LG_ANF.h"
#include "LG_Scene.h"
#include "LG_SceneInterface.h"
#include "LG_general.h"

int main(int argc, char * argv[]){
    
    
    
    
    CGFapplication app = CGFapplication();
    
    int result=0;
    
    try {
        app.init(&argc, argv);
        
        LG_Scene *scene=new LG_Scene();
        LG_SceneInterface *scene_interface = new LG_SceneInterface();
        
        
        const char * fileName=getDocumentName(argc, argv);

        scene->setDocName(fileName);
        
        
        app.setScene(scene);
        scene_interface->setLightsContainer(scene);
        scene_interface->setCamerasContainer(scene);
        scene_interface->setDrawing(scene);
        app.setInterface(scene_interface);
        
        //app.setInterface(new TPinterface());
        
        //result=Catch::Session().run(argc, argv);//run tests before starting app
        
        app.run();
    }
    catch(GLexception& ex) {
        cout << "GL error: " << ex.what();
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
