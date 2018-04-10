/*
* WarGame - small 2D game for studies
* Copyright (C) 2018  Bertrand Caplet <bbcorp@chunkz.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "../include/NetworkEngine.h"
#include "../../Client/include/wargame_generated.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
using asio::ip::udp;

engine::Network::Network()
{
	memset(m_buffer, 0, MAX_BUFFER);
	m_socket = new udp::socket(m_io_service, udp::endpoint(udp::v4(), PORT));
}
engine::Network::~Network()
{
	m_socket->close();
	delete m_socket;
}

void engine::Network::receiveLoop(void)
{
	size_t receiveLength(0);
	while (true)
	{
		try {
			receiveLength = m_socket->receive_from(
				asio::buffer(m_buffer, MAX_BUFFER), m_sender_enpoint);
			if (receiveLength > MAX_BUFFER)
				throw runtime_error("We receive more data than we can store !");
		}
		catch (exception const &e)
		{
			cerr << "ERROR: " << e.what() << endl;
		}
#ifdef _DEBUG
		std::cout << "Received " << receiveLength << " bytes of data: " << m_buffer << std::endl; // We've received data !!
#endif
		decodeFlatBuf(receiveLength);
		// reset the buffer
		memset(m_buffer, 0, MAX_BUFFER);
	}
}

using namespace WarGame::fb;

bool engine::Network::decodeFlatBuf(size_t receiveLength)
{

	// Make sure the buffer we received is OK
	flatbuffers::Verifier verifier(m_buffer, receiveLength);

	if (VerifyrequestIdBuffer(verifier))
	{
		auto request = flatbuffers::GetRoot<requestId>(m_buffer);
		if (request->newid() == -1)
		{
			flatbuffers::FlatBufferBuilder builder;
			uint16_t newID(m_Players.size());
			string name(request->name()->data());
			auto requestAnswer = CreaterequestIdDirect(builder, newID, name.data());
			FinishrequestIdBuffer(builder, requestAnswer);
			std::string send_buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
			builder.ReleaseBufferPointer();
			m_socket->send_to(asio::buffer(send_buffer), m_sender_enpoint);
			sendPlayersToClient(&m_sender_enpoint);
		}
		
	}
	else if (VerifyplayerBaseBuffer(verifier))
	{
		auto pBase = GetplayerBase(m_buffer);
		PlayerBase Player(pBase);
		Player.m_sender_enpoint = m_sender_enpoint;
		storePlayer(&Player);
		return true;
	}
	else
		return false; // Buffer is corrupted !
}

bool engine::Network::storePlayer(PlayerBase *Player)
{
	if (m_Players.size() == 0) // There's no player
	{
		m_Players.push_back(*Player);
		return true;
	}
	else // There is
	{
		for (uint16_t i = 0; i < m_Players.size(); i++)
		{
			if (m_Players.at(i) == *Player)
				return false; // Player already exist with same data, do not store !
			else if (m_Players.at(i).m_sender_enpoint == m_sender_enpoint && m_Players.at(i) != *Player) // Player exists but data has changed.
			{
				m_Players.at(i) = *Player;
				sendPlayerToAllClients(Player);
				return true;
			}
		}
		m_Players.push_back(*Player); // Player doesn't exist at all.
		sendPlayerToAllClients(Player);
		//sendPlayers();
		return true;
	}
}

size_t engine::Network::sendPlayerToAllClients(PlayerBase *Player)
{
	if (m_Players.size() == 1)
		return false; // Do not send if there's only one player, this is pointless !
	size_t sendLength(0);
	for (uint16_t i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i) == *Player)
			continue; // Do not send to ourself !
		sendLength += m_socket->send_to(asio::buffer(Player->encodeFlatBuf()), m_Players.at(i).m_sender_enpoint);
	}
	return sendLength;
}

size_t engine::Network::sendPlayersToClient(asio::ip::udp::endpoint *endpoint)
{
	if (m_Players.size() < 1)
		return false; // Do not send if there's only one player, this is pointless !
	flatbuffers::FlatBufferBuilder builder;
	// Create a vector of players
	vector<flatbuffers::Offset<playerBase>> vecStructFbPlayerBase;
	for (uint16_t i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i).m_sender_enpoint == *endpoint)
			continue; // Do not store if it's ourself !!
		vecStructFbPlayerBase.push_back(m_Players.at(i).returnStructFbPlayerbase(&builder));
	}
	// Close builder
	auto players = Createplayers(builder, builder.CreateVector<flatbuffers::Offset<playerBase>>(vecStructFbPlayerBase));
	FinishplayersBuffer(builder, players);
	// Store to buffer
	std::string send_buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return m_socket->send_to(asio::buffer(send_buffer), *endpoint);
}

/*size_t engine::Network::sendPlayersToClient(asio::ip::udp::endpoint *enpoint)
{
	if (m_Players.size() == 1)
		return false; // Do not send if there's only one player, this is pointless !
	size_t sendLength(0);
	for (uint16_t i = 0; i < m_Players.size(); i++)
	{
		flatbuffers::FlatBufferBuilder builder;
		// Create a vector of players
		vector<flatbuffers::Offset<playerBase>> vecStructFbPlayerBase;
		for (uint16_t j = 0; j < m_Players.size(); j++)
		{
			if (m_Players.at(i).m_sender_enpoint == m_Players.at(j).m_sender_enpoint)
				continue; // Do not store if it's ourself !!
			vecStructFbPlayerBase.push_back(m_Players.at(j).returnStructFbPlayerbase(&builder));
		}
		// Close builder
		auto players = Createplayers(builder, builder.CreateVector<flatbuffers::Offset<playerBase>>(vecStructFbPlayerBase));
		FinishplayersBuffer(builder, players);
		// Store to buffer
		std::string send_buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
		builder.ReleaseBufferPointer();
		sendLength += m_socket->send_to(asio::buffer(send_buffer), m_Players.at(i).m_sender_enpoint);
	}
	return sendLength;
}*/