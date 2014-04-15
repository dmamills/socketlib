#include <ClientSocket.hpp>
#include <iostream>
#include <string>
#include <fstream>
/*
   File transfer handshake

   CLIENT-> READY
   SERVER-> OK
   CLIENT-> FILENAME
   SERVER-> (FILESIZE/NOTFOUND)
   SERVER-> CHUNKS

*/

void requestFile(SocketLib::ClientSocket& client,std::string request_filename,std::string output_filename) {

	std::ofstream fstream(output_filename,std::ios::binary);

	if(fstream.is_open()) {
		std::cout <<"File opened\n";
		
		//Start file request, and wait for reply
		client.send("OK");
		std::string data;
		client.recv(data);
		if(data == "OK") {

			//send filename
			std::cout << "Got OK, sending filename\n";
			client.send(request_filename);
			client.recv(data);
			
			if(data != "NOTFOUND") {
				//get total file size
				std::cout <<"File size: " << data <<"\n";

				int fileSize = atoi(data.c_str());
				int bytesRecv = 0;

				//start chunk transfer
				client.send("OK");

				std::cout<<"Recieving chunks...\n";
				while(bytesRecv < fileSize) {

					//get chunk size, and reply
					client.recv(data);
					int chunkSize = atoi(data.c_str());
					client.send("OK");
		
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
			}	
		}
	} else {
		std::cout <<"Output file not able to be opened.\n";
	}
	fstream.close();
}


int main() {

	SocketLib::ClientSocket client("127.0.0.1",27015);
	std::string rf;
	std::string of;

	std::cout<<"request filename?";
	std::cin>>rf;

	std::cout<<"out filename?";
	std::cin>>of;
	requestFile(client,rf,of);
	return 0;
}