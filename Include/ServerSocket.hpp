#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <Socket.hpp>

namespace SocketLib {

class ServerSocket : public Socket {
public:
	ServerSocket();
	ServerSocket(int port);
	~ServerSocket();
};

}