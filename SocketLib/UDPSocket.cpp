#if !defined (GUARD_UDPSOCKET)
#define GUARD_UDPSOCKET

#if defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "SocketLib-mt-s-gd.lib")
#elif defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "SocketLib-mt-gd.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "SocketLib-mt-s.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "SocketLib-mt.lib")
#endif

#include <UDPSocket.hpp>


UDPSocket::UDPSocket() {}
UDPSocket::UDPSocket(std::string ip, unsigned short port, bool server) : Socket(ip,port,server,SOCK_DGRAM) {
	
	if(server) {
		bind();
	}

}
UDPSocket::~UDPSocket() { }

int UDPSocket::sendData(std::string data) {
	return sendto(_hSocket,data.c_str(),data.size(),0,(sockaddr*)&_addr,sizeof(_addr));
}

std::string UDPSocket::recieveData() {
	    sockaddr clientAddress;
		socklen_t cbClientAddress = sizeof(clientAddress);
		int const MAX_LINE = 256;
		char msg[MAX_LINE];

		int n = recvfrom(_hSocket,msg,MAX_LINE,0,&clientAddress,&cbClientAddress);
		msg[0] = toupper(msg[0]);
		msg[min(n,255)] = 0;
		std::string r = msg;
		return msg;
}

#endif