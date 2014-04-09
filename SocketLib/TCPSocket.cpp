#include <TCPSocket.hpp>


TCPSocket::TCPSocket() {}

TCPSocket::TCPSocket(std::string ip, unsigned short port, bool server) : Socket(ip,port,server,SOCK_STREAM) {

	if(server) {
		bind();
		listen();
	} else {
		connect();
	}
}


TCPSocket::~TCPSocket() {

}
