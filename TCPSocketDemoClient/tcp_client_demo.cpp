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
		
		std::string i;
		client.send("OK");
		std::string s;
		client.recv(s);

		if(s == "OK") {
			std::cout << "Got OK, sending filename\n";
			client.send(request_filename);
			client.recv(s);
				
			if(s != "NOTFOUND") {
				std::cout <<"File size: " << s <<"\n";
				int fileSize = atoi(s.c_str());
				int bytesRecv = 0;
				client.send("OK");

				std::cout<<"Recieving chunks...\n";
				while(bytesRecv < fileSize) {

					client.recv(s);
					int chunkSize = atoi(s.c_str());
					std::cout <<"Chunk will be: " << chunkSize << " bytes.\n";
					client.send("OK");
					std::vector<char> chunk;
					chunk.resize(chunkSize);
					int r = client.recv(chunk);
					std::cout <<"Got chunk size: " << r << "\n";

					/*if(r == 0) {
						std::cout<<"Connection closed, closing file.\n";
						break;
					}*/
					bytesRecv += r;
					for(const auto& c: chunk)
						fstream << c; //<<"\n";
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
	/*std::string rf;
	std::string of;

	std::cout<<"request filename?";
	std::cin>>rf;

	std::cout<<"out filename?";
	std::cin>>of;*/
	requestFile(client,"in.jpg","out2.jpg");
	return 0;
}