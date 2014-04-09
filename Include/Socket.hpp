#if !defined (GUARD_SOCKET)
#define GUARD_SOCKET

#if defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "SocketLib-mt-s-gd.lib")
#elif defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "SocketLib-mt-gd.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "SocketLib-mt-s.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "SocketLib-mt.lib")
#endif

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")
#include <string>

class Socket {

public:
	Socket();
	Socket(std::string,unsigned short,bool,int);
	~Socket();
	void close();


protected:
	sockaddr_in _addr;
	SOCKET _hSocket;

	bool bind();
	bool listen();
	bool connect();

private:
	std::string _ipAddr;
	unsigned short _portAddr;
	WSADATA _wsa;
	

	bool initWSA();
	bool initSocket(int);

};


#endif