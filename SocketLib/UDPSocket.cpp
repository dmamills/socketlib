#include <UDPSocket.hpp>


UDPSocket::UDPSocket() {}
UDPSocket::UDPSocket(std::string ip, unsigned short port, bool server) : Socket(ip,port,server,SOCK_DGRAM) { }
UDPSocket::~UDPSocket() { }

int UDPSocket::sendData(std::string data) {
	return sendto(_hSocket,data.c_str(),data.size(),0,(sockaddr*)&_addr,sizeof(_addr));
}

std::string UDPSocket::recieveData() {
	char recieve[MAX_SIZE+1];
	int n = recvfrom(_hSocket,recieve,MAX_SIZE,0,NULL,NULL);

	if(n == -1) {
		std::cerr<<"NO REPLY FROM SERVER\n";
		return "";
	} else {
		recieve[n] = 0;
		std::string data = recieve;
		return data;
	}
}