#include <ClientSocket.hpp>
#include <iostream>
#include <string>
#include <fstream>

int main() {

	SocketLib::ClientSocket client("127.0.0.1",27015);
	std::ofstream fstream("out.md",std::ios::binary);

	if(fstream.is_open()) {
		std::cout <<"File opened\n";
		
		std::string i;
		while(getline(std::cin,i)) {
		
			client.send(i);
			std::string s;
			int r = client.recv(s);
			std::cout <<"File size: " << s <<"\n";
			int fileSize = atoi(s.c_str());
			int bytesRecv = 0;
			client.send("OK");

			std::cout<<"Recieving chunks...\n";
			while(bytesRecv < fileSize) {
				std::string chunk;
				int r = client.recv(chunk);
				std::cout <<"Got chunk size: " << r << "\n";

				if(r == 0) {
					break;
				}
				bytesRecv += r;
				fstream << chunk;

			}
			break;
		}
	} else {
		std::cout <<"FILE NOT OPENED!\n";
	}
	fstream.close();
	return 0;
}