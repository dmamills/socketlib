#include <ServerSocket.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

int main() {
	
	SocketLib::ServerSocket server(27015);

	while(1) {
		SocketLib::ServerSocket connection;
		server.accept(connection);

		std::string data;
		while(1) {
			std::ifstream fstream("in.jpg",std::ios::binary);

			if(fstream.is_open()) {
				
				connection.recv(data);
				 if(data == "READY") {

					 std::streambuf* buffer = fstream.rdbuf();
					 std::ostringstream oss;
					 oss << buffer;

					 connection.send(oss.str());
				 }
				 fstream.close();
			} else {
				std::cout<<"UNABLE TO OPEN FILE!\n";
			}
			 break;
		}
		break;
	}
	
	return 0;
}