#include <ClientSocket.hpp>
#include <iostream>
#include <string>
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


void requestFile(SocketLib::ClientSocket& client,std::string request_filename,std::string output_filename) {

	std::ofstream fstream(output_filename,std::ios::binary);

	if(fstream.is_open()) {
		std::cout <<"File opened\n";
		std::string data;
		//Start file request, and wait for reply
		client << "OK";
		client >> data;
		
		if(data == "OK") {

			//send filename
			std::cout << "Got OK, sending filename\n";
			client << request_filename;
			client >> data;
			
			if(data != "NOTFOUND") {
				//get total file size
				std::cout <<"File size: " << data <<"\n";

				int fileSize = atoi(data.c_str());
				int bytesRecv = 0;

				//start chunk transfer
				client << "OK";

				std::cout<<"Recieving chunks...\n";
				while(bytesRecv < fileSize) {

					//get chunk size, and reply
					client >> data;
					int chunkSize = atoi(data.c_str());
					client <<"OK";
		
					//set vector to chunksize and recieve data
					std::vector<char> chunk;
					chunk.resize(chunkSize);
					int r = 0;
					if( chunkSize > 0 ){
						r = client.recv(chunk);
					}
					else{
						break;
					}
					//increment byte counter
					bytesRecv += r;

					//stream chunk into file
					for(const auto& c: chunk)
						fstream << c;
				}
				std::cout <<"Recieved: " << bytesRecv << " bytes.\n";
			}	
		}
	} else {
		std::cout <<"Output file not able to be opened.\n";
	}
	fstream.close();
}


int main(int argc, char* argv[]) {

	SocketLib::ClientSocket client("127.0.0.1",27015);

	if(argc<2) {
		std::cout<<"usage: TCPSocketClientDemo.exe <request filename> <download name>\n";
		return EXIT_FAILURE;
	}

	std::cout<<"Requesting " << argv[1] << "from server, saving as " << argv[2] << "\n";
	requestFile(client,argv[1],argv[2]);
	return 0;
}