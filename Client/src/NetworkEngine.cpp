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
#include "../include/wargame_generated.h"
#include "../include/ft_Delay.h"
#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;
using asio::ip::udp;

engine::Network::Network(const string address, engine::Game *GameEngine) : m_receiver_endpoint(asio::ip::address::from_string(address), PORT), m_socket(NULL), m_thread_receiveLoop(NULL), m_thread_streamMainPlayerData(NULL)
{
	m_socket = new udp::socket(m_io_service);
	m_socket->open(udp::v4());
	m_thread_streamMainPlayerData = new thread(&engine::Network::streamMainPlayerData, this, GameEngine);
	m_thread_receiveLoop = new thread(&engine::Network::receiveLoop, this, GameEngine);
}
engine::Network::~Network()
{
	if (m_socket != NULL)
	{
		m_socket->shutdown(m_socket->shutdown_both);
		m_socket->close();
		delete m_socket;
	}
	if (m_thread_streamMainPlayerData != NULL)
	{
		m_thread_streamMainPlayerData->join();
		delete m_thread_streamMainPlayerData;
	}
	if (m_thread_receiveLoop != NULL)
	{
		m_thread_receiveLoop->join();
		delete m_thread_receiveLoop;
	}
}

size_t engine::Network::sendData(std::string *send_buffer)
{
	return m_socket->send_to(asio::buffer(*send_buffer), m_receiver_endpoint);
}

void engine::Network::streamMainPlayerData(engine::Game *GameEngine)
{
	MainPlayer lastMainPlayer;
	sf::Clock clockPlayerData;

	string send_buffer;
	requestIdTry(&GameEngine->m_MainPlayer, 3);

	while (true)
	{
		if (GameEngine->m_MainPlayer != lastMainPlayer && engine::ft_Delay(&clockPlayerData, sf::milliseconds(14)))
		{
				send_buffer = GameEngine->m_MainPlayer.encodeFlatBuf();
				size_t sendLength = sendData(&send_buffer);
				lastMainPlayer = GameEngine->m_MainPlayer;
		}
		this_thread::sleep_for(100us);
	}
}

bool engine::Network::requestIdTry(MainPlayer *o_MainPlayer, const uint16_t retryTimes)
{
	/* Send Request ID */
	string send_buffer(o_MainPlayer->requestId());
	size_t sendLength = sendData(&send_buffer);
	this_thread::sleep_for(50ms);
	uint16_t i(1);
	while (i <= retryTimes)
	{
		for (uint16_t j = 0; j < 5; j++) // 500 ms total
		{
			try {
				if (o_MainPlayer->m_id != -1)
					return true;
				else
				{
					this_thread::sleep_for(100ms);
					throw runtime_error("Server not answering: waiting 100ms");
				}
			}
			catch (exception const &e)
			{
				cerr << "ERROR: " << e.what() << endl;
			}
		}
		try {
			if (o_MainPlayer->m_id != -1)
				return true;
			else
			{
				string error("Server not answering: retry ");
				error += to_string(i) + " of " + to_string(retryTimes);
				throw runtime_error(error);
			}
		}
		catch (exception const &e)
		{
			cerr << "ERROR: " << e.what() << endl;
		}
		i++;
	}
	try {
		string error("Server not answering after ");
		error += to_string(retryTimes) + " tries";
		throw ios_base::failure(error);
	}
	catch (exception const &e)
	{
		cerr << "ERROR: " << e.what() << endl;
		exit(-1);
	}
	return false;

}

void engine::Network::receiveLoop(engine::Game *GameEngine)
{
	size_t receiveLength(0);
	udp::endpoint server_endpoint;
	while (true)
	{
		try {
			receiveLength = m_socket->receive_from(
				asio::buffer(m_receive_buffer, MAX_BUFFER), server_endpoint);
			if (receiveLength > MAX_BUFFER)
				throw runtime_error("We receive more data than we can store !");
		}
		catch (exception const &e)
		{
			cerr << "ERROR: " << e.what() << endl;
		}
#ifdef _DEBUG
		std::cout << "Received " << receiveLength << " bytes of data: " << m_receive_buffer << std::endl; // We've received data !!
#endif
		decodeFlatBuf(receiveLength, GameEngine);
		// reset the buffer
		memset(m_receive_buffer, 0, MAX_BUFFER);
	}
}

using namespace WarGame::fb;

bool engine::Network::decodeFlatBuf(size_t receiveLength, engine::Game *GameEngine)
{
	// Make sure the buffer we received is OK
	flatbuffers::Verifier verifier(m_receive_buffer, receiveLength);

	if (VerifyrequestIdBuffer(verifier))
	{
		auto requestIdAnswer = flatbuffers::GetRoot<requestId>(m_receive_buffer);
		if (GameEngine->m_MainPlayer.m_id == -1)
			GameEngine->m_MainPlayer.m_id = requestIdAnswer->newid();
	}
	else if (VerifyplayerBaseBuffer(verifier))
	{
		bool found(false);
		auto pBase = flatbuffers::GetRoot<playerBase>(m_receive_buffer);
		Player o_tempPlayer(pBase);
		for (uint16_t i = 0; i < GameEngine->m_MainPlayer.m_ennemiesPlayers.size(); i++)
		{
			if (o_tempPlayer.m_name == GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i).m_name && o_tempPlayer.m_id == GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i).m_id) // Player already exists
			{
				if (GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i) == o_tempPlayer)
				{
					found = true;
					break; // Data is the same, no need to store
				}
				else
				{
					found = true;
					GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i).applyModificationFromNetwork(&o_tempPlayer); // Data has changed so store it !
					GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i).updateState();
					break; // No need to go further we found it.
				}
			}
		}
		if (!found) // We didn't find it locally !
		{
			o_tempPlayer.updateState();
			GameEngine->m_MainPlayer.m_ennemiesPlayers.push_back(o_tempPlayer); // So, store it !
			GameEngine->m_ennemiesCount++;
			return true;
		}
	}
	else if (VerifyplayersBuffer(verifier))
	{
		auto fbPlayers = flatbuffers::GetRoot<players>(m_receive_buffer);
		// Store new ones
		if (GameEngine->m_MainPlayer.m_ennemiesPlayers.size() == 0) // There's no player
		{
			for (uint16_t i = 0; i < fbPlayers->vecPlayers()->size(); i++)
			{
				Player o_tempPlayer(fbPlayers->vecPlayers()->Get(i));
				o_tempPlayer.updateState();
				GameEngine->m_MainPlayer.m_ennemiesPlayers.push_back(o_tempPlayer);
				GameEngine->addSpriteToQueue(&GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i).m_sprite);
				GameEngine->m_ennemiesCount++;
			}
			return true;
		}
		else if (GameEngine->m_MainPlayer.m_ennemiesPlayers.size() > 0)
		{
			bool found(false);
			uint16_t i;
			uint16_t j;
			for (i = 0; i < fbPlayers->vecPlayers()->size(); i++)
			{
				found = false;
				Player o_tempPlayer(fbPlayers->vecPlayers()->Get(i));
				for (j = 0; j < GameEngine->m_MainPlayer.m_ennemiesPlayers.size(); j++)
				{
					if (o_tempPlayer.m_name == GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).m_name && o_tempPlayer.m_id == GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).m_id) // Player already exists
					{
						if (GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j) == o_tempPlayer)
						{
							found = true;
							break; // Data is the same, no need to store
						}
						else
						{
							found = true;
							GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).applyModificationFromNetwork(&o_tempPlayer); // Data has changed so store it !
							GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).updateState();
							break; // No need to go further we found it.
						}
					}
				}
				if (!found) // We didn't find it locally !
				{
					o_tempPlayer.updateState();
					GameEngine->m_MainPlayer.m_ennemiesPlayers.push_back(o_tempPlayer); // So, store it !
					GameEngine->m_ennemiesCount++;
				}
			}
		}
	}
	else
		return false; // Buffer is corrupted !
}