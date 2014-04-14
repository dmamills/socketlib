#include <Socket.hpp>
using namespace SocketLib;

Socket::Socket() {
	initWSA();
	initSocket(SOCK_STREAM);
}

//cleanup after yo self
Socket::~Socket() {
	close();
}

bool Socket::bind(int port) {

  _portAddr = port;
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(_portAddr);

  return !(::bind ( _hSocket,( struct sockaddr * ) &_addr, sizeof (_addr ) ) == SOCKET_ERROR);
}


bool Socket::listen() {
	return !(::listen(_hSocket,BACKLOG_NUM) == SOCKET_ERROR);
}

bool Socket::accept(Socket& conn) {
  int addr_length = sizeof(_addr);
  conn._hSocket = ::accept( _hSocket, ( SOCKADDR* ) &_addr, ( socklen_t * ) &addr_length );
  return (conn._hSocket > 0);
}

bool Socket::connect(std::string ip, int port) {

	_ipAddr = ip;
	_portAddr = port;

	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_portAddr);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	return !(::connect ( _hSocket, (SOCKADDR*) &_addr, sizeof ( _addr )) == SOCKET_ERROR);
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

	int protocol = (type == SOCK_STREAM) ? IPPROTO_TCP : 0;
	_hSocket = socket(AF_INET,type,protocol);

	//success!
	if (_hSocket != INVALID_SOCKET) {
		return true;
	}

	//failure?
	std::cerr<<"Error occured in Socket::initSocket\n";
	close();
	return false;
}

int Socket::send(std::string data) { 

	return ::send(_hSocket,data.c_str(),data.length(),0);
}

int Socket::recv(std::string& data) {

	char buf[MAX_SIZE];

	int r = ::recv(_hSocket,buf,MAX_SIZE,0);

	data = buf;
	return r;
}

void Socket::close() {
	closesocket(_hSocket);
	WSACleanup();
}