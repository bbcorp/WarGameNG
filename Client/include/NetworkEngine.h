#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H
#include <errno.h>
#include <string>
#include <vector>
#include <asio.hpp>

#define PORT 1977
#define MAX_BUFFER 4096

namespace engine
{
	class Network
	{
	public:
		Network(const std::string address);
		size_t engine::Network::sendData(std::string *send_buffer);

	private:
		asio::ip::udp::endpoint m_receiver_endpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket *m_socket;
		//asio::ip::udp::socket m_socket;
		/*private:
		asio::ip::udp::endpoint m_receiver_endpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket m_socket;
		char m_send_buffer[MAX_BUFFER];*/
	};
}
#endif