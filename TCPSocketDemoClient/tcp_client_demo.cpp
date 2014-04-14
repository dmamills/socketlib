#include <ClientSocket.hpp>
#include <iostream>
#include <string>

int main() {

	SocketLib::ClientSocket client("127.0.0.1",27015);

	std::string data;
	std::string in;

	while(getline(std::cin,in)) {
		std::cout<<"Sending: " << in << "\n";
		client.send(in);
		client.recv(data);
		std::cout << "Recieved: " << data << "\n";

		data.clear();
		in.clear();
	}
	

	return 0;
}