#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "LG_Basic_Scene.h"


using std::cout;
using std::exception;


int main(int argc, char* argv[]) {
    
    CGFapplication app = CGFapplication();
    
    try {
        app.init(&argc, argv);
        
        app.setScene(new LG_Basic_Scene());
        app.setInterface(new CGFinterface());
        //app.setInterface(new TPinterface());
        
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
    
    return 0;
}