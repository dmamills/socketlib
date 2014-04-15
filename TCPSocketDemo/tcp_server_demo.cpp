#include <ServerSocket.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


void sendFile(SocketLib::ServerSocket& connection) {
	
		std::string data;
		while(1) {
			std::ifstream fstream("test.md", std::ios::in | std::ios::binary| std::ios::ate);

			if(fstream.is_open()) {
				
				//Start file transfer
				 connection.recv(data);

				 if(data == "READY") {
					 std::cout <<"Got ready, sending size\n";
					 std::string d;
					 int fsize = fstream.tellg();
					 connection.send(std::to_string(fsize));
					 connection.recv(d);

					 if(d == "OK") {
						 std::cout <<"File Size recieved.\nSending Chunks...";

						 fstream.seekg(0,fstream.beg);
						 std::string s;
						 while(std::getline(fstream,s)) {
							int bytesSent = connection.send(s);
							std::cout<<"chunk of size " << bytesSent << " sent...\n";
						}
					}
				 }
				 fstream.close();
			} else {
				std::cout<<"UNABLE TO OPEN FILE!\n";
			}
			 break;
		}
}


int main() {
	
	SocketLib::ServerSocket server(27015);

	while(1) {
		SocketLib::ServerSocket connection;
		server.accept(connection);
		sendFile(connection);
		break;
	}
	return 0;
}