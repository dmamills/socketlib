#include <Socket.hpp>


class TCPSocket : public Socket {

public:
	TCPSocket();
	TCPSocket(std::string, unsigned short, bool);
	~TCPSocket();

private:
	bool initSocket();
};