#include <Socket.hpp>

namespace SocketLib {

class ServerSocket : public Socket {
public:
	ServerSocket();
	ServerSocket(int port);
	~ServerSocket();
};

}