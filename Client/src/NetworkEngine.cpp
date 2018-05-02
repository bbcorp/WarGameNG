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

engine::Network::Network(const string address, engine::Game *GameEngine) : m_receiver_endpoint(asio::ip::address::from_string(address), PORT), m_socket(nullptr), m_thread_streamMainPlayerData(nullptr), m_thread_receiveLoop(nullptr), m_GameEngine(GameEngine)
{
	m_socket = new udp::socket(m_io_service);
	m_socket->open(udp::v4());
	m_thread_streamMainPlayerData = new thread(&engine::Network::streamMainPlayerData, this);
	m_thread_receiveLoop = new thread(&engine::Network::receiveLoop, this);
}
engine::Network::~Network()
{
	if (m_socket != nullptr)
	{
		m_socket->shutdown(m_socket->shutdown_both);
		m_socket->close();
		delete m_socket;
	}
	if (m_thread_streamMainPlayerData != nullptr)
	{
		m_thread_streamMainPlayerData->join();
		delete m_thread_streamMainPlayerData;
	}
	if (m_thread_receiveLoop != nullptr)
	{
		m_thread_receiveLoop->join();
		delete m_thread_receiveLoop;
	}
}

size_t engine::Network::sendData(std::string *send_buffer)
{
	return m_socket->send_to(asio::buffer(*send_buffer), m_receiver_endpoint);
}

void engine::Network::streamMainPlayerData(void)
{
	MainPlayer lastMainPlayer;
	sf::Clock clockPlayerData;

	requestIdTry(&m_GameEngine->m_MainPlayer, 3);

	while (true)
	{
		if (
			(m_GameEngine->m_MainPlayer != lastMainPlayer
			&& engine::ft_Delay(&clockPlayerData, sf::milliseconds(14)))
			|| engine::ft_Delay(&clockPlayerData, sf::milliseconds(500)) // keepalive
			)
		{
			sendPlayerData();
			sendPlayerBullets();
			lastMainPlayer = m_GameEngine->m_MainPlayer;
		}
		this_thread::sleep_for(100us);
	}
}

void engine::Network::sendPlayerData(void)
{
	m_send_buffer = m_GameEngine->m_MainPlayer.encodeFlatBuf();
	size_t sendLength = sendData(&m_send_buffer);
}

void engine::Network::sendPlayerBullets(void)
{
	m_GameEngine->m_mutex.lock();
	for (vector<Bullet>::iterator bullet = m_GameEngine->m_MainPlayer.m_bulletQueue.begin(); bullet != m_GameEngine->m_MainPlayer.m_bulletQueue.end(); bullet++)
	{
		m_send_buffer = bullet->encodeFlatBuf();
		size_t sendLength = sendData(&m_send_buffer);
		bullet = m_GameEngine->m_MainPlayer.m_bulletQueue.erase(bullet);
		if (bullet == m_GameEngine->m_MainPlayer.m_bulletQueue.end())
			break;
	}
	m_GameEngine->m_mutex.unlock();
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
		for (uint16_t j = 0; j < 5; j++) // 1200 ms total
		{
			try {
				if (o_MainPlayer->m_id != -1)
					return true;
				else
				{
					this_thread::sleep_for(300ms);
					throw runtime_error("Server not answering: waiting 300ms");
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

void engine::Network::receiveLoop(void)
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
		std::cout << "Received " << receiveLength << " bytes of data." << std::endl; // We've received data !!
#endif
		decodeFlatBuf(receiveLength);
		// reset the buffer
		memset(m_receive_buffer, 0, MAX_BUFFER);
	}
}

using namespace WarGame::fb;

bool engine::Network::decodeFlatBuf(size_t receiveLength)
{
	// Make sure the buffer we received is OK
	flatbuffers::Verifier verifier(m_receive_buffer, receiveLength);

	if (VerifyrequestIdBuffer(verifier))
	{
		auto requestIdAnswer = flatbuffers::GetRoot<requestId>(m_receive_buffer);
		if (m_GameEngine->m_MainPlayer.m_id == -1)
		{
			m_GameEngine->m_MainPlayer.m_id = requestIdAnswer->newId();
			m_GameEngine->m_MainPlayer.updatePosition(requestIdAnswer->newX(), requestIdAnswer->newY());
		}
	}
	else if (VerifyplayerBaseBuffer(verifier))
	{
		if (processplayerBaseBuffer())
			return true;
	}
	else if (VerifyplayersBuffer(verifier))
	{
		if (processplayersBuffer())
			return true;
	}
	else if (VerifybulletsBuffer(verifier))
	{
		if (processbulletsBuffer())
			return true;
	}
	else if (VerifydeleteBulletBuffer(verifier))
	{
		if (processdeleteBulletBuffer())
			return true;
	}
	else
		return false; // Buffer is corrupted !
}

bool engine::Network::processplayerBaseBuffer(void)
{
	bool found(false);
	auto pBase = flatbuffers::GetRoot<playerBase>(m_receive_buffer);
	Player o_tempPlayer(pBase);
	if (o_tempPlayer.m_id == m_GameEngine->m_MainPlayer.m_id && o_tempPlayer.m_name == m_GameEngine->m_MainPlayer.m_name && o_tempPlayer.m_health != m_GameEngine->m_MainPlayer.m_health)
	/* if this is ourself and health has changed */
	{
		m_GameEngine->m_MainPlayer.m_health = o_tempPlayer.m_health;
		return true;		
	}
	for (Player o_Player : m_GameEngine->m_MainPlayer.m_ennemiesPlayers)
	{
		if (o_tempPlayer.m_name == o_Player.m_name && o_tempPlayer.m_id == o_Player.m_id) // Player already exists
		{
			if (o_Player == o_tempPlayer)
			{
				found = true;
				break; // Data is the same, no need to store
			}
			else
			{
				found = true;
				o_Player.applyModificationFromNetwork(&o_tempPlayer); // Data has changed so store it !
				o_Player.updateState();
				break; // No need to go further we found it.
			}
		}
	}
	if (!found) // We didn't find it locally !
	{
		o_tempPlayer.updateState();
		m_GameEngine->m_MainPlayer.m_ennemiesPlayers.push_back(o_tempPlayer); // So, store it !
		m_GameEngine->m_ennemiesCount++;
		return true;
	}
}

bool engine::Network::processplayersBuffer(void)
{
	auto fbPlayers = flatbuffers::GetRoot<players>(m_receive_buffer);
	// Store new ones
	if (m_GameEngine->m_MainPlayer.m_ennemiesPlayers.size() == 0) // There's no player
	{
		for (uint16_t i = 0; i < fbPlayers->vecPlayers()->size(); i++)
		{
			Player o_tempPlayer(fbPlayers->vecPlayers()->Get(i));
			o_tempPlayer.updateState();
			m_GameEngine->m_MainPlayer.m_ennemiesPlayers.push_back(o_tempPlayer);
			m_GameEngine->addSpriteToQueue(&m_GameEngine->m_MainPlayer.m_ennemiesPlayers.at(i).m_sprite);
			m_GameEngine->m_ennemiesCount++;
		}
		return true;
	}
	else if (m_GameEngine->m_MainPlayer.m_ennemiesPlayers.size() > 0)
	{
		bool found(false);
		uint16_t i;
		uint16_t j;
		for (i = 0; i < fbPlayers->vecPlayers()->size(); i++)
		{
			found = false;
			Player o_tempPlayer(fbPlayers->vecPlayers()->Get(i));
			for (j = 0; j < m_GameEngine->m_MainPlayer.m_ennemiesPlayers.size(); j++)
			{
				if (o_tempPlayer.m_name == m_GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).m_name && o_tempPlayer.m_id == m_GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).m_id) // Player already exists
				{
					if (m_GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j) == o_tempPlayer)
					{
						found = true;
						break; // Data is the same, no need to store
					}
					else
					{
						found = true;
						m_GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).applyModificationFromNetwork(&o_tempPlayer); // Data has changed so store it !
						m_GameEngine->m_MainPlayer.m_ennemiesPlayers.at(j).updateState();
						break; // No need to go further we found it.
					}
				}
			}
			if (found)
				continue;
			else // We didn't find it locally !
			{
				o_tempPlayer.updateState();
				m_GameEngine->m_MainPlayer.m_ennemiesPlayers.push_back(o_tempPlayer); // So, store it !
				m_GameEngine->m_ennemiesCount++;
			}
		}
	}
	return true; // FIXME
}

bool engine::Network::processbulletsBuffer(void)
{
	auto fbBullets = flatbuffers::GetRoot<bullets>(m_receive_buffer);
	for (uint16_t bullet = 0; bullet < fbBullets->vecBullets()->size(); bullet++)
	{
		bool found(false);
		engine::Bullet tempBullet(fbBullets->vecBullets()->Get(bullet));
		//m_GameEngine->m_MainPlayer.m_bullets.push_back(tempBullet);
		for (vector<Bullet>::iterator localBullet = m_GameEngine->m_MainPlayer.m_bullets.begin(); localBullet != m_GameEngine->m_MainPlayer.m_bullets.end(); localBullet++)
		{
			if (tempBullet == *localBullet) // Bullet found and it's the same
			{
				found = true;
				break;

			}
			else if (tempBullet.m_id == localBullet->m_id && tempBullet.m_ownerId == localBullet->m_ownerId) // Bullet found but with different positions
			{
				*localBullet = tempBullet; // So store new coordinates
				found = true;
				break;
			}
		}
		if (!found)
		{
			m_GameEngine->m_MainPlayer.m_bullets.push_back(tempBullet);
		}
	}
	return true; // FIXME
}

bool engine::Network::processdeleteBulletBuffer(void)
{
	bool found(false);
	auto dBullet = flatbuffers::GetRoot<deleteBullet>(m_receive_buffer);
	for (vector<Bullet>::iterator localBullet = m_GameEngine->m_MainPlayer.m_bullets.begin(); localBullet != m_GameEngine->m_MainPlayer.m_bullets.end(); localBullet++)
	{
		if (dBullet->id() == localBullet->m_id && dBullet->ownerId() == localBullet->m_ownerId)
		{
			m_GameEngine->m_mutex.lock();
			found = true;
			localBullet = m_GameEngine->m_MainPlayer.m_bullets.erase(localBullet);
			m_GameEngine->m_mutex.unlock();
		}
		if (localBullet == m_GameEngine->m_MainPlayer.m_bullets.end())
			break;
	}
	return found;
}