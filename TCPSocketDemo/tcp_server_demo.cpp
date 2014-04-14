#include <ServerSocket.hpp>
#include <string>
#include <iostream>
#include <vector>


int main() {
	
	SocketLib::ServerSocket server(27015);
	std::vector<SocketLib::ServerSocket> connections;

	while(1) {
		SocketLib::ServerSocket connection;
		connections.push_back(server.accept(connection));

		while(1) {
			std::string data;
			connection >> data; //connection.recv(data);

			std::cout<<"recv: " << data << "\n";
			connection << data; //connection.send(data);

			if(data == "LEAVE ME ALONE") break;
			
			data.clear();
		}
	}
	
	return 0;
}