#include <stdlib.h>
#include <iostream>
#include <string>
#include <asio.hpp>
#define PORT 1977
#define MAX_LENGTH 4096

using asio::ip::udp;

void server(asio::io_service& io_service, unsigned short port)
{
	udp::socket sock(io_service, udp::endpoint(udp::v4(), port));
	for (;;)
	{
		char data[MAX_LENGTH];
		memset(data, 0, MAX_LENGTH);
		udp::endpoint sender_endpoint;
		size_t length = sock.receive_from(
			asio::buffer(&data, MAX_LENGTH), sender_endpoint);
		std::cout << "Received " << length << " bytes of data: " << data << std::endl;
		//sock.send_to(asio::buffer(data, length), sender_endpoint);
	}
}


/*void server(asio::ioservice &io_service, uint16_t port)
{

}*/

int main(int argc, int *argv[])
{
	asio::io_service io_service;
	server(io_service, PORT);
		
	return EXIT_SUCCESS;
}

