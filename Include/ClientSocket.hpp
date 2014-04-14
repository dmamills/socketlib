#include <Socket.hpp>
namespace SocketLib {

class ClientSocket : public Socket {
public:
	ClientSocket(std::string,int);
	~ClientSocket();

};

}