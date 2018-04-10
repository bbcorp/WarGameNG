#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H
#include <errno.h>
#include <string>
#include <vector>
#include <asio.hpp>
#include <SFML/System/Clock.hpp>
#include "../include/PlayerBase.h"

#define PORT 1977
#define MAX_BUFFER 4096

namespace engine
{
	class Network
	{
	public:
		Network();
		virtual ~Network();
		void receiveLoop(void);

	private:
		bool decodeFlatBuf(size_t receiveLength);
		bool storePlayer(PlayerBase *Player);
		size_t sendPlayerToAllClients(PlayerBase *Player);
		size_t sendPlayersToClient(asio::ip::udp::endpoint *endpoint);

		asio::ip::udp::endpoint m_sender_enpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket *m_socket;
		std::vector<PlayerBase> m_Players;
		
		uint8_t m_buffer[MAX_BUFFER];
	};
}
#endif