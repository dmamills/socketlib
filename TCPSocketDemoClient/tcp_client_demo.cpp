#include <ClientSocket.hpp>
#include <iostream>
#include <string>
#include <fstream>

int main() {

	SocketLib::ClientSocket client("127.0.0.1",27015);
	std::ofstream fstream("out.jpg",std::ios::binary);

	if(fstream.is_open()) {
		std::cout <<"File opened\n";
		
		std::string i;
		while(getline(std::cin,i)) {
		
			client.send(i);
			std::string data;

			client.recv(data);
			fstream << data;
	
		}
	} else {
		std::cout <<"FILE NOT OPENED!\n";
	}
	fstream.close();
	//std::string data;
	//std::string in;

	//while(getline(std::cin,in)) {
	//	std::cout<<"Sending: " << in << "\n";
	//	client.send(in);
	//	client.recv(data);
	//	std::cout << "Recieved: " << data << "\n";

	//	data.clear();
	//	in.clear();
	//}
	//

	return 0;
}