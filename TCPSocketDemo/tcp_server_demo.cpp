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

	//send chunk size
	connection.send(std::to_string(chunk.size()));

	//wait for OK reply
	std::string data;
	connection.recv(data);

	//send chunk
	if(data == "OK") {
		bytesSent = connection.send(chunk);
	}
	return bytesSent;
}

void sendFile(SocketLib::ServerSocket& connection) {
	
		std::string data;
		while(true) {
				
				 connection.recv(data);
				 if(data == "OK") {
					std::cout <<"Got OK, waiting for name.\n";

					//reply, and wait for filename
					connection.send("OK");
					connection.recv(data);

					//try and open file
					std::ifstream fstream(data, std::ios::in | std::fstream::binary);
					if(fstream.is_open()) {
					
					 std::cout <<"Able to open " << data << ", sending size\n";

					 //get file size
					 std::streampos start = fstream.tellg();
					 fstream.seekg(0,std::ios::end);
					 std::streampos end = fstream.tellg();
					 fstream.seekg(0,std::ios::beg);			 
					 int fsize = static_cast<int>(end-start);

					 //send the size
					 connection.send(std::to_string(fsize));
					 connection.recv(data);

					 if(data == "OK") {
						 std::cout <<"File Size recieved.\nSending Chunks...";

						 //go back to start of file stream
						 fstream.seekg(0,fstream.beg);

						 //read file into memory
						 std::vector<char> contents;
						 contents.resize(fsize);
						 fstream.read(&contents[0],contents.size());


						 //buffer vector
						 std::vector<char> buffer;
						 int cs = 0;
						 for(const char&c : contents) {
							 cs++;
							 buffer.push_back(c);

							 //if chunk reached max size, send it!
							 if(cs == MAX_SIZE) {
								 int bytesSent = sendChunk(connection,buffer);
								 buffer.clear();
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