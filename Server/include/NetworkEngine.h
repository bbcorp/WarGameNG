#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H
#include <errno.h>
#include <string>
#include <vector>
#include <thread>
#include <asio.hpp>
#include <SFML/System/Clock.hpp>
#include "../include/PlayerBase.h"
#include "../include/Bullet.h"

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
		size_t sendBulletsToAllClients(std::string *buffer);
		void checkPlayerTimeout(void);
		void checkBulletCollision(void);

		asio::ip::udp::endpoint m_sender_enpoint;
		asio::io_service m_io_service;
		asio::ip::udp::socket *m_socket;
		std::vector<PlayerBase> m_Players;
		std::vector<Bullet> m_Bullets;

		std::thread *m_thread_player_timeout;
		std::thread *m_thread_check_bullet_collision;
		
		uint8_t m_buffer[MAX_BUFFER];
	};
}
#endif