
#include <CGFapplication.h>
#include <iostream>
#include <string>
#include "LG_ANF.h"
#include "LG_Scene.h"

int main(int argc, char * argv[]){
    
    
    
    
    CGFapplication app = CGFapplication();
    
    int result=0;
    
    try {
        app.init(&argc, argv);
        
        LG_Scene *scene=new LG_Scene();
        scene->setDocName("LAIG_TP1_ANF_T06_G01_v3.anf");
        
        
        app.setScene(scene);
        app.setInterface(new CGFinterface());
        //app.setInterface(new TPinterface());
        
        //result=Catch::Session().run(argc, argv);//run tests before starting app
        
        app.run();
    }
    catch(GLexception& ex) {
        cout << "Erro: " << ex.what();
        return -1;
    }
    catch(exception& ex) {
        cout << "Erro inesperado: " << ex.what();
        return -1;
    }
    
    
    
    return result;
    
}
