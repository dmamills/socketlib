#include <Socket.hpp>

class UDPSocket : public Socket {
public:
	UDPSocket();
	UDPSocket(std::string,unsigned short,bool); 
	~UDPSocket();

	int sendData(std::string);
	std::string recieveData();
protected:

private:
	

};