#include <iostream>
#include <UDPSocket.hpp>


using namespace std;

int main() {
	//UDPSocket(std::string ip, unsigned short port, bool server) 
	UDPSocket socket("127.0.0.1",49153,true);

	for(;;) {
		std::string data = socket.recieveData();
		std::cout <<"RECIEVED: " << data << "\n";
	}

	return 0;
}