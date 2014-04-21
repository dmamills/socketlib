#include <ServerSocket.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>


/*
   File transfer handshake

   CLIENT-> OK
   SERVER-> OK
   CLIENT-> FILENAME
   SERVER-> (FILESIZE/NOTFOUND)
   CLIENT-> OK
   LOOP
     SERVER-> CHUNK SIZE
	 SERVER-> CHUNK

*/

int sendChunk(SocketLib::ServerSocket& connection,std::vector<char> chunk) {
	
	int bytesSent = -1;
    std::string data;

	//send chunk size and wait for OK reply
	connection << std::to_string(chunk.size());
	connection >> data;

	//send chunk
	if(data == "OK") {
		bytesSent = connection.send(chunk);
	}
	return bytesSent;
}

void sendFile(SocketLib::ServerSocket connection) {
	
	std::cout <<"Started connection thread #" << std::this_thread::get_id() << "\n";
	std::string data;
	while(true) {

		connection >> data;

		if(data == "OK") {
		std::cout <<"Got OK, waiting for name.\n";

		//reply, and wait for filename
		connection << "OK";
		connection >> data;

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
			connection << std::to_string(fsize); 
			connection >> data;
					
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
				int totalBytesSent = 0;
				for(const char&c : contents) {
					cs++;
					buffer.push_back(c);

					//if chunk reached max size, send it!
					if(cs == MAX_SIZE) {
						int bytesSent = sendChunk(connection,buffer);
						totalBytesSent += bytesSent;
						buffer.clear();
						cs = 0;
					}
				}
				//send last chunk!
				int bytesSent = sendChunk(connection,buffer);
				totalBytesSent += bytesSent;
				std::cout <<"Sent " << totalBytesSent << " bytes\n";
			}
				std::cout<<"Closing file stream\n";
				fstream.close();

			} else {

			std::cout<<"Requested file << " << data << " not found.\n";
			connection.send("NOTFOUND");
		}
			break;
		}
	}
}

void threadfunc(SocketLib::ServerSocket* conn) {
		sendFile(*conn);	
}

int main() {

	SocketLib::ServerSocket server(27015);
	std::vector<std::thread> threads;
	std::vector<SocketLib::ServerSocket*> connections;
	const int MAX_FILES_SENT = 5;
	int c= 0;

	std::cout << "Server initialized, will send " << MAX_FILES_SENT << " files before shutting down.\n";
	std::cout <<"Waiting for connections...\n";

	while(c < MAX_FILES_SENT) {
		SocketLib::ServerSocket* connection = new SocketLib::ServerSocket();
		if(server.accept(*connection)) {
			c++;
			std::cout << "Connection established, " << c << " files \n";
			threads.push_back(std::thread(threadfunc,connection));
			connections.push_back(connection);
			
		} else {
			delete connection;
		}
	}

	std::cout<<"Maximum files transferred, server shutdown, and cleaning up.\n";
	
	for(auto& t:threads)t.join();
	while(!connections.empty()) {
		delete connections.back();
		connections.pop_back();
	}

	return 0;
}