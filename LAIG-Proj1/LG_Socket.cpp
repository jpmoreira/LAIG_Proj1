//
//  LG_Socket.cpp
//  Sockets
//
//  Created by José Pedro Moreira on 01/01/15.
//  Copyright (c) 2015 José Pedro Moreira. All rights reserved.
//

#include "LG_Socket.h"

using std::string;

#ifndef _WIN32

LG_Socket::LG_Socket(string address,int port){

    
    this->sock=socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0)throw new std::exception();
    
    
    struct hostent *server;
    
    server=gethostbyname(address.c_str());
    if (server==NULL)throw new std::exception();
    
    
    struct sockaddr_in serv_addr;
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    
    serv_addr.sin_port = htons(port);
    
    if (connect(sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)throw new std::exception();
    
    
    

}

#else
#include <winsock2.h>
LG_Socket::LG_Socket(string address, int port){


	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
	else
		printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		throw new std::exception();
	}
	else
		printf("Client: socket() is OK.\n");

	// Connect to a server.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	// Just test using the localhost, you can try other IP address
	clientService.sin_addr.s_addr = inet_addr(address.c_str());
	clientService.sin_port = htons(port);

	if (connect(sock, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		WSACleanup();
		throw new std::exception();
	}
	else {
		printf("Client: connect() is OK.\n");
		printf("Client: Can start sending and receiving data...\n");
	}

	// Send and receive data.
	printf("Connected\n");
}






#endif

void LG_Socket::write(string textToSend){


	send(sock, textToSend.c_str(), textToSend.length(), 0);

}

string LG_Socket::read(){



	int pos = 0;
	while (true) {
		recv(sock, &recieveBuffer[pos], 1, 0);
		if (recieveBuffer[pos] == '\n')
			break;
		pos++;
	}
	if (recieveBuffer[pos - 1] == '\r')
		recieveBuffer[pos - 1] = 0;
	recieveBuffer[pos] = 0;// null terminator
	return string(recieveBuffer);

}
