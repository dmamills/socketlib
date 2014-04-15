#include <ServerSocket.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


/*
   File transfer handshake

   CLIENT-> READY
   SERVER->OK
   CLIENT->FILENAME
   SERVER-> (FILESIZE/NOTFOUND)
   SERVER->CHUNKS

*/

int sendChunk(SocketLib::ServerSocket& connection,std::vector<char> chunk) {
	
	int bytesSent = -1;
	connection.send(std::to_string(chunk.size()));
	std::string data;
	connection.recv(data);
	if(data == "OK") {
		bytesSent = connection.send(chunk);
	}
	return bytesSent;
}

void sendFile(SocketLib::ServerSocket& connection) {
	
		std::string data;
		while(1) {
					
				//Start file transfer
				 connection.recv(data);
				 if(data == "OK") {
					std::cout <<"Got OK, waiting for name.\n";
					connection.send("OK");
					connection.recv(data);
					std::ifstream fstream(data, std::ios::in | std::fstream::binary);
					if(fstream.is_open()) {
					
					 std::cout <<"Able to open " << data << ", sending size\n";
					 std::string d;

					 std::streampos start = fstream.tellg();
					 fstream.seekg(0,std::ios::end);
					 std::streampos end = fstream.tellg();
					 fstream.seekg(0,std::ios::beg);

					 
					 int fsize = static_cast<int>(end-start);
					 connection.send(std::to_string(fsize));
					 connection.recv(d);

					 if(d == "OK") {
						 std::cout <<"File Size recieved.\nSending Chunks...";

						 fstream.seekg(0,fstream.beg);
						 std::string s;

						 std::vector<char> contents;
						 contents.resize(fsize);
						 fstream.read(&contents[0],contents.size());

						 std::vector<char> buf;
						 int cs = 0;
						 for(const char&c : contents) {
							 cs++;
							 buf.push_back(c);
							 if(cs > 256) {
								 std::cout<<"size of oss: " << buf.size() << "\n";
								 int bytesSent = sendChunk(connection,buf);
								 std::cout<<"chunk of size " << bytesSent << " sent...\n";
								 buf.clear();
								 cs = 0;
							 }
						 }
					}
					 fstream.close();
				 } else {
					std::cout<<"Requested file << " << data << " not found.\n";
					connection.send("NOTFOUND");
			}
			 break;
		}
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