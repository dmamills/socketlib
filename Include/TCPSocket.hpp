#if !defined (GUARD_TCPSOCKET)
#define GUARD_TCPSOCKET

#if defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "SocketLib-mt-s-gd.lib")
#elif defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "SocketLib-mt-gd.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "SocketLib-mt-s.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "SocketLib-mt.lib")
#endif


#include <Socket.hpp>


class TCPSocket : public Socket {

public:
	TCPSocket();
	TCPSocket(std::string, unsigned short, bool);
	~TCPSocket();

private:
	bool initSocket();
};

#endif