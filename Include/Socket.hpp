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