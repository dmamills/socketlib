#include <ServerSocket.hpp>
#include <string>
#include <iostream>


int main() {
	
	SocketLib::ServerSocket server(27015);
	
	while(true) {
		SocketLib::ServerSocket connection;
		server.accept(connection);

		while(true) {
			std::string data;
			connection.recv(data);

			std::cout<<"recv: " << data << "\n";
			connection.send(data);
			
			data.clear();
		}
	}
	
	return 0;
}