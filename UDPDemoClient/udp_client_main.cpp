#include <iostream>
#include <UDPSocket.hpp>


using namespace std;

int main() {
	//UDPSocket(std::string ip, unsigned short port, bool server) 
	UDPSocket socket("127.0.0.1",49153,false);

	std::string in;
	while(getline(cin,in)) {
		int r = socket.sendData(in);
		std::cout << "Result: " << r << "\n";

	}
	return 0;
}

