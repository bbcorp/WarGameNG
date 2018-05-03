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

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../include/GameEngine.h"

using namespace std;

sf::Texture *engine::Game::m_ennemy_texture(nullptr);

engine::Game::Game(uint16_t width, uint16_t height) : m_ennemiesCount(0), m_window(nullptr), m_width(width), m_height(height)
{
	m_MainPlayer.m_name = "bbcorp";
	sfmlInit();
	engine::Map::getInstance();
}

engine::Game::Game() : m_ennemiesCount(0), m_window(nullptr), m_width(800), m_height(600)
{
	m_MainPlayer.m_name = "bbcorp";
	sfmlInit();
	engine::Map::getInstance();
}

engine::Game::~Game()
{
	sfmlCleanup();
}

engine::Game& engine::Game::getInstance(void)
{
	static Game instance;
	return instance;
}

void engine::Game::sfmlInit(void)
{
	sfmlCreateWindow();
	sfmlLoadAllTextures();
	sfmlLoadPlayerTexture("../res/character.png");
	sfmlCreateEnnemyTexture();
}

bool engine::Game::sfmlCleanup(void)
{
	sfmlDestroyTextures();
	if (m_window != nullptr)
	{
		delete m_window;
		m_window = NULL;
	}
	return true;
}

void engine::Game::sfmlCreateWindow(void)
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "WarGame");
	//m_window->setVerticalSyncEnabled(true);
	m_window->setFramerateLimit(120);
}

void engine::Game::sfmlRender(void)
{
	// création d'une vue à partir de la zone rectangulaire du monde 2D à voir
	sf::View LastView = m_MainPlayer.m_PlayerView;
	m_window->setView(m_MainPlayer.m_PlayerView);
	uint16_t ennemiesCount(0);
	engine::Event engineEvent(m_window, &m_MainPlayer);
	sf::Font font;
	if (!font.loadFromFile("../res/calibri.ttf"))
		return;
	sf::Text text;
	text.setString("Bonjour !");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Red);
	while (m_window->isOpen())
	{
		engineEvent.handleEvents();
		m_window->clear();
		if (m_MainPlayer.m_PlayerView.getCenter() != LastView.getCenter()) // If view has changed
		{
			m_window->setView(m_MainPlayer.m_PlayerView); // Set the new view
			LastView = m_MainPlayer.m_PlayerView; // Reset LastView
		}
		if (m_ennemiesCount > ennemiesCount) // A new player is connected
		{
			sfmlLoadEnnemiesTexture("../res/ennemy.png", m_ennemiesCount);
			ennemiesCount = m_ennemiesCount;
		}
		sfmlDisplaySprites();
		m_window->draw(text);
		drawBullets();
		//drawWalls();
		m_window->display();
			
	}
}
void engine::Game::sfmlDisplaySprites(void)
{
	for (sf::Sprite *sprite : m_spriteQueue)
		m_window->draw(*sprite);
}

bool engine::Game::deleteSpriteFromQueue(sf::Sprite *o_sprite)
{
	for (vector<sf::Sprite*>::iterator sprite = m_spriteQueue.begin(); sprite != m_spriteQueue.end(); sprite++)
	{
		if (o_sprite == &**(sprite))
		{
			m_spriteQueue.erase(sprite);
			return true;
		}
	}
	return false;	
}

void engine::Game::addSpriteToQueue(sf::Sprite *o_sprite)
{
	m_spriteQueue.push_back(o_sprite);
}

void engine::Game::drawWalls(void)
{
	std::vector<sf::FloatRect> walls(engine::Map::getWalls());
	for (uint16_t i = 0; i < walls.size(); i++)
	{
		sf::RectangleShape rect;
		rect.setPosition(sf::Vector2f(walls.at(i).left, walls.at(i).top));
		rect.setSize(sf::Vector2f(walls.at(i).width, walls.at(i).height));
		rect.setFillColor(sf::Color::Red);
		m_window->draw(rect);
	}
}

void engine::Game::drawBullets(void)
{
	m_mutex.lock();
	for (Bullet bullet : m_MainPlayer.m_bullets)
	{
		sf::RectangleShape rect;
		rect.setPosition(sf::Vector2f(bullet.m_src_x, bullet.m_src_y));
		rect.setSize(sf::Vector2f(bullet.m_w, bullet.m_h));
		rect.setFillColor(sf::Color::Black);
		m_window->draw(rect);
	}
	m_mutex.unlock();
}


void engine::Game::sfmlLoadAllTextures(void)
{
	// LOAD HERE all textures needed
	sfmlLoadTexture("../res/background_dev.png");
}

void engine::Game::sfmlLoadTexture(string fileName)
{
	sf::Texture *texture = new sf::Texture;
	try {
		if (!texture->loadFromFile(fileName))
			throw string("Can't load " + fileName);
	}
	catch (string const& exception)
	{
		cerr << exception << endl;
		sf::err();
		return;
	}
	texture->setSmooth(true);
	sf::Sprite *sprite = new sf::Sprite(*texture);
	m_spriteQueue.push_back(sprite);
}

void engine::Game::sfmlLoadPlayerTexture(string fileName)
{
	sf::Texture *texture = new sf::Texture;
	try {
		if (!texture->loadFromFile(fileName))
			throw string("Can't load " + fileName);
	}
	catch (string const& exception)
	{
		cerr << exception << endl;
		sf::err();
		return;
	}
	texture->setSmooth(true);
	m_MainPlayer.m_sprite.setTexture(*texture);
	m_spriteQueue.push_back(&m_MainPlayer.m_sprite);
}

void engine::Game::sfmlLoadEnnemiesTexture(string fileName, uint16_t position)
{
	if (m_MainPlayer.m_ennemiesPlayers.size() < position)
		return;
	position--;
	sf::Texture *texture = new sf::Texture;
	try {
		if (!texture->loadFromFile(fileName))
			throw string("Can't load " + fileName);
	}
	catch (string const& exception)
	{
		cerr << exception << endl;
		sf::err();
		return;
	}
	texture->setSmooth(true);
	m_MainPlayer.m_ennemiesPlayers.at(position).m_sprite.setTexture(*texture);
	m_spriteQueue.push_back(&m_MainPlayer.m_ennemiesPlayers.at(position).m_sprite);
}

void engine::Game::sfmlCreateEnnemyTexture(void)
{
	m_ennemy_texture = new sf::Texture;
	try {
		if (!m_ennemy_texture->loadFromFile("../res/ennemy.png"))
			throw string("Can't load ../res/ennemy.png");
	}
	catch (string const& exception)
	{
		cerr << exception << endl;
		sf::err();
		return;
	}
	m_ennemy_texture->setSmooth(true);
}

void engine::Game::EnnemiesPlayersUpdateState(void)
{
	/* NO NEED ? */
	for (Player o_Player : m_MainPlayer.m_ennemiesPlayers)
		o_Player.updateState();
}

void engine::Game::sfmlDestroyTextures(void)
{
	for (sf::Sprite *sprite : m_spriteQueue)
		delete sprite->getTexture();
}