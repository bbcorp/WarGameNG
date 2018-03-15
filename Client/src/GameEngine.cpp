#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "../include/GameEngine.h"
#include "../include/Event.h"

using namespace std;

engine::Game::Game(uint16_t width, uint16_t height) : m_width(width), m_height(height), m_window(NULL)
{
	m_MainPlayer.m_name = "bbcorp";
	sfmlInit();
}

void engine::Game::sfmlInit(void)
{
	sfmlCreateWindow();
	sfmlLoadAllTextures();
	sfmlLoadPlayerTexture("../res/character.png");
}

bool engine::Game::sfmlCleanup(void)
{
	sfmlDestroyTextures();
	delete m_window;
	m_window = NULL;
	return true;
}

void engine::Game::sfmlCreateWindow(void)
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "WarGame");
	m_window->setVerticalSyncEnabled(true);
}

void engine::Game::sfmlRender(void)
{
	engine::Event GameEvent;
	while (m_window->isOpen())
	{
		GameEvent.handleEvents(m_window);
		GameEvent.handleKeyboard(&m_MainPlayer);
		m_MainPlayer.updateOrientation();
		m_window->clear();
		sfmlDisplaySprites();
		m_window->display();
	}
	sfmlCleanup();
}
void engine::Game::sfmlDisplaySprites(void)
{
	for (uint16_t i = 0; i < m_spriteQueue.size(); i++)
		m_window->draw(*m_spriteQueue[i]);
}
void engine::Game::sfmlLoadAllTextures(void)
{
	// LOAD HERE all textures needed
	sfmlLoadTexture("../res/background_dev.png");
	sfmlLoadTexture("../res/blood.png");
}

void engine::Game::sfmlLoadTexture(string fileName)
{
	sf::Texture *texture = new sf::Texture;
	try {
		if (!texture->loadFromFile(fileName))
		{
			throw string("Can't load " + fileName);
		}
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
		{
			throw string("Can't load " + fileName);
		}
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

void engine::Game::sfmlDestroyTextures(void)
{
	for (uint16_t i = 0; i < m_spriteQueue.size(); i++)
		delete m_spriteQueue[i]->getTexture();
}