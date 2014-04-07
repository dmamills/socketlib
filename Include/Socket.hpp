#if !defined (GUARD_SOCKET_LIB)
#define GUARD_SOCKET_LIB

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
#include <winsock.h>
#include <string>

class Socket {

public:
	Socket();
	Socket(std::string,unsigned short,bool);
	~Socket();
	void close();

	

private:
	std::string _ipAddr;
	unsigned short _portAddr;
	SOCKET _hSocket;
	WSADATA _wsa;
	sockaddr_in _addr;

	bool initWSA();
	bool initSocket();
	bool bind();
	bool listen();
	bool connect();
	
};


#endif