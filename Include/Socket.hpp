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
#include <sstream>

namespace SocketLib {

#define BACKLOG_NUM 10
#define MAX_SIZE 256

class Socket {

public:
	Socket();
	virtual ~Socket();
	void close();

	bool bind(int);
	bool listen();
	bool accept(Socket&);
	bool connect(std::string,int);

	int send(std::string);
	int recv(std::string&);

	int send(std::streambuf*);
	//int recv(std::streambuf&);

	Socket& operator << (std::string);
	Socket& operator >> (std::string&);

private:

	sockaddr_in _addr;
	SOCKET _hSocket;
	std::string _ipAddr;
	unsigned short _portAddr;
	WSADATA _wsa;

	bool initWSA();
	bool initSocket(int);
};

}
#endif