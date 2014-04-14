#include <ServerSocket.hpp>


SocketLib::ServerSocket::ServerSocket() : Socket() {}

SocketLib::ServerSocket::ServerSocket(int port)  {

	if(!bind(port)) {
		std::cerr<<"Error in bind\n";
		close();
	}

	if(!listen()) {
		std::cerr<<"Error in listen\n";
		close();
	}
}

SocketLib::ServerSocket::~ServerSocket() { }