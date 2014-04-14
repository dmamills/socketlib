#include <ClientSocket.hpp>
#include <iostream>

SocketLib::ClientSocket::ClientSocket(std::string ip,int port) : Socket() {

	if(!connect(ip,port)) {
		std::cerr <<"Error in ClientSocket::connect() \n";
		close();
	} else {
		std::cout <<"Connected to " << ip << ":"<< port <<"\n";
	}
}

SocketLib::ClientSocket::~ClientSocket() { }