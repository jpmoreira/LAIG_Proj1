//
//  LG_Socket.h
//  Sockets
//
//  Created by José Pedro Moreira on 01/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#ifndef __Sockets__LG_Socket__
#define __Sockets__LG_Socket__



#include <string>

#ifndef _WIN32
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#else
#pragma comment(lib, "Ws2_32.lib")

//#include <iostream>

#endif // !_WIN32
#define ADDRESS "127.0.0.1"
#define HOSTPORT 60070 


class LG_Socket {
#ifndef _WIN32
    int sock;
#else
	unsigned int sock;	
#endif

    char recieveBuffer[2048];

    
public:

	LG_Socket(std::string address = std::string(ADDRESS), int port = HOSTPORT);
    void write(std::string textToSend);   
    std::string read();
    
};

#endif /* defined(__Sockets__LG_Socket__) */
