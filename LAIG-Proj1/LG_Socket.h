//
//  LG_Socket.h
//  Sockets
//
//  Created by José Pedro Moreira on 01/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __Sockets__LG_Socket__
#define __Sockets__LG_Socket__

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <netdb.h>

class LG_Socket {
    
    int sock;

    char recieveBuffer[256];
    
public:

    LG_Socket(std::string address,int port);
    
    void write(std::string textToSend);
    
    std::string read();
    
};

#endif /* defined(__Sockets__LG_Socket__) */
