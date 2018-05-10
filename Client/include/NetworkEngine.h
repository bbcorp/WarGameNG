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
		Network(Network const&) = delete;
		void operator=(Network const&) = delete;
		static Network& getInstance(std::string address, engine::Game *GameEngine);
		size_t sendData(std::string *send_buffer);

	private:
		Network(const std::string address, engine::Game *GameEngine);
		~Network();
		bool requestIdTry(MainPlayer *o_MainPlayer, const uint16_t retryTimes);
		void streamMainPlayerData(void);
		void receiveLoop(void);
		bool decodeFlatBuf(size_t receiveLength);
		bool processplayerBaseBuffer(void);
		bool processplayersBuffer(void);
		bool processbulletsBuffer(void);
		bool processdeleteBulletBuffer(void);
		void sendPlayerData(void);
		void sendPlayerBullets(void);

		asio::io_service m_io_service;
		asio::ip::udp::resolver m_resolver;
		asio::ip::udp::resolver::query m_resolver_query;
		asio::ip::udp::endpoint m_receiver_endpoint;
		asio::ip::udp::socket *m_socket;
		std::thread *m_thread_streamMainPlayerData;
		std::thread *m_thread_receiveLoop;
		uint8_t m_receive_buffer[MAX_BUFFER];
		std::string m_send_buffer;
		engine::Game *m_GameEngine;
	};
}
#endif