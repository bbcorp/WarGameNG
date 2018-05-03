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
#include "../include/Logger.h"
#include "../include/ft_Delay.h"
#include "../include/Map.h"
#include <iostream>
#include <thread>
#include <stdlib.h>

using namespace std;
using asio::ip::udp;

engine::Network::Network() : m_socket(nullptr), m_thread_player_timeout(nullptr), m_thread_check_bullet_collision(nullptr)
{
	memset(m_buffer, 0, MAX_BUFFER);
	m_socket = new udp::socket(m_io_service, udp::endpoint(udp::v4(), PORT));
#ifdef NDEBUG
	m_thread_player_timeout = new thread(&engine::Network::checkPlayerTimeout, this);
#endif // NDEBUG
	m_thread_check_bullet_collision = new thread(&engine::Network::processBullets, this);
	engine::Map::getInstance();
	receiveLoop();
}

engine::Network::~Network()
{
	if (m_thread_check_bullet_collision != nullptr)
	{
		m_thread_player_timeout->join();
		delete m_thread_player_timeout;
	}
	if (m_thread_player_timeout != nullptr)
	{
		m_thread_check_bullet_collision->join();
		delete m_thread_check_bullet_collision;
	}
	if (m_socket != nullptr)
	{
		m_socket->close();
		delete m_socket;
	}
}

engine::Network& engine::Network::getInstance()
{
	static Network instance;
	return instance;
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
		std::cout << "Received " << receiveLength << " bytes of data." << std::endl; // We've received data !!
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
		if (request->newId() == -1)
		{
			flatbuffers::FlatBufferBuilder builder;
			uint16_t newID(m_Players.size());
			sf::Vector2u newPos(engine::Map::getSpawn());
			auto requestAnswer = CreaterequestIdDirect(builder, newID, request->name()->data(), newPos.x, newPos.y);
			FinishrequestIdBuffer(builder, requestAnswer);
			std::string send_buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
			builder.ReleaseBufferPointer();
			m_socket->send_to(asio::buffer(send_buffer), m_sender_enpoint);
			sendPlayersToClient(&m_sender_enpoint);
			stringstream message(request->name()->data());
			message << " has connected with " << newPos.x << "," << newPos.y << " position";
			engine::Logger::log(message.str(), 0);
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
	else if (VerifybulletBuffer(verifier))
	{
		auto bullet = Getbullet(m_buffer);
		engine::Bullet o_bullet(bullet);
		m_mutex.lock();
		m_Bullets.push_back(o_bullet);
		m_mutex.unlock();
		// TODO: send to other players
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
		for (vector<PlayerBase>::iterator player = m_Players.begin(); player != m_Players.end(); player++)
		{
			if (*player == *Player)
			{
				player->m_clock.restart();
				return false; // Player already exist with same data, do not store !
			}
			else if (player->m_sender_enpoint == m_sender_enpoint && *player != *Player) // Player exists but data has changed.
			{
				*player = *Player;
				sendPlayerToAllClients(Player, 0);
				return true;
			}
		}
		m_Players.push_back(*Player); // Player doesn't exist at all.
		sendPlayerToAllClients(Player, 0);
		//sendPlayers();
		return true;
	}
}

size_t engine::Network::sendPlayerToAllClients(PlayerBase *Player, bool playerHasChanged)
{
	if (m_Players.size() == 1)
		return false; // Do not send if there's only one player, this is pointless !
	size_t sendLength(0);
	for (vector<PlayerBase>::iterator player = m_Players.begin(); player != m_Players.end(); player++)
	{
		if (*player == *Player && !playerHasChanged)
			continue; // Do not send to ourself !*/
		sendLength += m_socket->send_to(asio::buffer(Player->encodeFlatBuf()), player->m_sender_enpoint);
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
	for (vector<PlayerBase>::iterator player = m_Players.begin(); player != m_Players.end(); player++)
	{
		if (player->m_sender_enpoint == *endpoint)
			continue; // Do not store if it's ourself !!
		vecStructFbPlayerBase.push_back(player->returnStructFbPlayerbase(&builder));
	}
	// Close builder
	auto players = Createplayers(builder, builder.CreateVector<flatbuffers::Offset<playerBase>>(vecStructFbPlayerBase));
	FinishplayersBuffer(builder, players);
	// Store to buffer
	std::string send_buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return m_socket->send_to(asio::buffer(send_buffer), *endpoint);
}


void engine::Network::checkPlayerTimeout(void)
{
	while (true)
	{
		this_thread::sleep_for(100ms);
		for (vector<PlayerBase>::iterator player = m_Players.begin(); player != m_Players.end(); player++)
		{
			if (engine::ft_Delay(&player->m_clock, sf::milliseconds(1000)))
			{
				engine::Logger::log(player->m_name + " has been disconnected, reason: timeout.", 0);
				player = m_Players.erase(player);
				if (player == m_Players.end())
					break;
			}
		}
	}
}

void engine::Network::processBullets(void)
{
	sf::FloatRect tempPlayer;
	sf::FloatRect tempBullet;
	while (true)
	{
		if (m_Bullets.size() > 0)
		{
			flatbuffers::FlatBufferBuilder builder;
			// Create a vector of bullets
			vector<flatbuffers::Offset<bullet>> vecStructFbBullet;
			m_mutex.lock();
			for (vector<Bullet>::iterator bullet = m_Bullets.begin(); bullet != m_Bullets.end(); bullet++)
			{
				bullet->calculateNextPixel();
				tempBullet = sf::FloatRect(bullet->m_src_x, bullet->m_src_y, bullet->m_w, bullet->m_h);
				if (engine::Map::mapIntersection(&tempBullet))
				{
					sendMessageToAllClients(bullet->encodeFlatBufDelete());
					bullet = m_Bullets.erase(bullet);
					if (bullet == m_Bullets.end())
						break;
				}
				for (vector<PlayerBase>::iterator player = m_Players.begin(); player != m_Players.end(); player++)
				{
					tempPlayer = sf::FloatRect(player->m_pos.x, player->m_pos.y, 30, 30);
					if (bullet->m_ownerId != player->m_id && tempBullet.intersects(tempPlayer))
					{
						player->receiveDamage(10);
						sendPlayerToAllClients(&*player, 1);
						sendMessageToAllClients(bullet->encodeFlatBufDelete());
						bullet = m_Bullets.erase(bullet);
						break;
					}
				}
				if (bullet == m_Bullets.end())
					break;
				vecStructFbBullet.push_back(bullet->returnStructFbBullet(&builder));
			}
			m_mutex.unlock();
			// Close builder
			if (vecStructFbBullet.size() > 0)
			{
				auto bullets = Createbullets(builder, builder.CreateVector<flatbuffers::Offset<bullet>>(vecStructFbBullet));
				FinishbulletsBuffer(builder, bullets);
				// Store to buffer
				std::string send_buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
				builder.ReleaseBufferPointer();
				// Send to all clients
				sendMessageToAllClients(send_buffer);
			}
		}
		this_thread::sleep_for(10ms);
	}
}

size_t engine::Network::sendMessageToAllClients(string const& buffer)
{
	size_t sendLength(0);
	for (vector<PlayerBase>::iterator player = m_Players.begin(); player != m_Players.end(); player++)
		sendLength += m_socket->send_to(asio::buffer(buffer), player->m_sender_enpoint);
	return sendLength;
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