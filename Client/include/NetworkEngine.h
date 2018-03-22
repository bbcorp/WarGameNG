#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H
#include "../include/GameEngine.h"
#include <errno.h>
#include <string>
#include <thread>
#include <vector>
#include <asio.hpp>

#define PORT 1977
#define MAX_BUFFER 4096

namespace engine
{
	class Network
	{
	public:
		Network(const std::string address, engine::Game *GameEngine);
		virtual ~Network();
		size_t sendData(std::string *send_buffer);
		void streamMainPlayerData(engine::Game *GameEngine);

	private:
		asio::ip::udp::endpoint m_receiver_endpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket *m_socket;
		std::thread *m_thread_streamMainPlayerData;
		//asio::ip::udp::socket m_socket;
		/*private:
		asio::ip::udp::endpoint m_receiver_endpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket m_socket;
		char m_send_buffer[MAX_BUFFER];*/
	};
}
#endif