#include <Socket.hpp>


//WHY
Socket::Socket() {}

Socket::Socket(std::string ip,unsigned short port,bool server = false,int type) {
	_ipAddr = ip;
	_portAddr = port;

	initWSA();
	initSocket(type);

	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	_addr.sin_port = htons(port);

}

//cleanup after yo self
Socket::~Socket() {
	close();
}


bool Socket::initWSA() {
	auto r = WSAStartup(MAKEWORD(2,2), &_wsa);
	//wsa success
	if( r == NO_ERROR) {
		return true;
	}

	//failure?
	close();
	return false;
}

bool Socket::initSocket(int type) {

	_hSocket = socket(AF_INET,type, 0);

	//success!
	if (_hSocket != INVALID_SOCKET) {
		return true;
	}

	//failure?
	std::cerr<<"Error occured in Socket::initSocket\n";
	close();
	return false;
}

bool Socket::connect() {
	if(::connect(_hSocket,(SOCKADDR*)&_addr,sizeof(_addr)) == SOCKET_ERROR) {
		std::cerr<<"ERROR occured in Socket::connect\n";
		close();
		return false;
	}
	return true;
}

bool Socket::bind() {
	if(::bind(_hSocket,(SOCKADDR*)&_addr,sizeof(_addr)) == SOCKET_ERROR) {
		std::cerr<<"ERROR OCCURED in Socket::bind\n";
		close();
		return false;
	}
	return true;
}

bool Socket::listen() {
	if(::listen(_hSocket,1) == SOCKET_ERROR) {
		std::cerr<<"ERROR OCCURED in Socket::listen\n";
		close();
		return false;
	}
	return true;
}

void Socket::close() {
	closesocket(_hSocket);
	WSACleanup();
}