#include "../include/NetworkEngine.h"
#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;
using asio::ip::udp;

engine::Network::Network(const string address,engine::Game *GameEngine) : m_receiver_endpoint(asio::ip::address::from_string(address), PORT)
{
	m_socket = new udp::socket(m_io_service);
	m_socket->open(udp::v4());
	m_thread_streamMainPlayerData = new thread(&engine::Network::streamMainPlayerData, this, GameEngine);

}
engine::Network::~Network()
{
	m_socket->shutdown(m_socket->shutdown_both);
	m_socket->close();
	delete m_socket;
	m_thread_streamMainPlayerData->join();
	delete m_thread_streamMainPlayerData;
}

size_t engine::Network::sendData(std::string *send_buffer)
{
	return m_socket->send_to(asio::buffer(*send_buffer), m_receiver_endpoint);
}

void engine::Network::streamMainPlayerData(engine::Game *GameEngine)
{
	PlayerBase lastMainPlayer;
	while (true)
	{
		if (GameEngine->m_MainPlayer != lastMainPlayer)
		{
			string send_buffer(GameEngine->m_MainPlayer.encodeFlatBuf());
			size_t sendLength = sendData(&send_buffer);
			lastMainPlayer = GameEngine->m_MainPlayer;
		}
		Sleep(100);
	}
}