#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H
#include "GameEngine.h"
#include "Player.h"
#include <errno.h>
#include <string>
#include <thread>
#include <vector>
#include <asio.hpp>
#include <SFML/System/Clock.hpp>

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
		void receiveLoop(engine::Game *GameEngine);
		bool decodeFlatBuf(size_t receiveLength, engine::Game *GameEngine);

	private:
		bool requestIdTry(MainPlayer *o_MainPlayer, const uint16_t retryTimes);
		asio::ip::udp::endpoint m_receiver_endpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket *m_socket;
		std::thread *m_thread_streamMainPlayerData;
		std::thread *m_thread_receiveLoop;
		uint8_t m_receive_buffer[MAX_BUFFER];
	};
}
#endif