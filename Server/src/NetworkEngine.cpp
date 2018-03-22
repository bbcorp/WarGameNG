#include "../include/NetworkEngine.h"
#include "../../Client/include/wargame_generated.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
using asio::ip::udp;

engine::Network::Network()
{
	memset(buffer, 0, MAX_BUFFER);
	m_socket = new udp::socket(m_io_service, udp::endpoint(udp::v4(), PORT));
}
engine::Network::~Network()
{
	m_socket->close();
	delete m_socket;
}

void engine::Network::receiveLoop(void)
{
	while (true)
	{
		size_t receiveLength = m_socket->receive_from(
			asio::buffer(buffer, MAX_BUFFER), m_sender_enpoint);
		std::cout << "Received " << receiveLength << " bytes of data: " << buffer << std::endl; // We've received data !!
		decodeFlatBuf(&string(buffer, receiveLength), receiveLength);
		memset(buffer, 0, MAX_BUFFER);
		// if decode -> store sender_endpoint
		//sock.send_to(asio::buffer(data, length), sender_endpoint);
	}
}

using namespace WarGame::fb;

bool engine::Network::decodeFlatBuf(std::string *buffer, size_t receiveLength)
{

	// Make sur the buffer we received is a playerBase
	flatbuffers::Verifier verifier((const uint8_t*)buffer->data(), receiveLength);
	if (!VerifyplayerBaseBuffer(verifier))
		return false;
	auto pBase = GetplayerBase(buffer->data());
	PlayerBase Player(pBase);
	Player.m_sender_enpoint = m_sender_enpoint;
	if (m_Players.size() == 0) // There's no player
	{
		m_Players.push_back(Player);
		return true;
	}
	else // There is
	{
		for (uint16_t i = 0; i < m_Players.size(); i++)
		{
			if (m_Players.at(i) == Player)
				return false; // Player already exist with same data, do not store !
			else if (m_Players.at(i).m_sender_enpoint == m_sender_enpoint && m_Players.at(i) != Player)
			{
				m_Players.at(i) = Player;
				return true;
			}
		}
		m_Players.push_back(Player);
	}
}