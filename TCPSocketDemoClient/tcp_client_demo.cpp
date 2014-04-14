#include <ClientSocket.hpp>
#include <iostream>
#include <string>

int main() {

	SocketLib::ClientSocket client("127.0.0.1",27015);

	std::string data;
	std::string in;

	while(getline(std::cin,in)) {
		std::cout<<"sending: " << in << "\n";
		client.send(in);
		client.recv(data);
		std::cout << "got: " << data << "\n";

		data.clear();
		in.clear();
	}
	

	return 0;
}