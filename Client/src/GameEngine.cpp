#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "../include/GameEngine.h"

using namespace std;

void GameEngine::sfmlInit(void)
{
	sfmlCreateWindow();
}

bool GameEngine::sfmlCleanup(void)
{
	sfmlDestroyTextures();
	delete window;
	window = NULL;
	return true;
}

void GameEngine::sfmlCreateWindow(void)
{
	width = 800;
	height = 600;
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WarGame");
	window->setVerticalSyncEnabled(true);
}

void GameEngine::sfmlRender(void)
{
	sfmlLoadTexture("../res/background_dev.png");
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		window->clear();
		sfmlDisplaySprites();
		window->display();
	}
	sfmlCleanup();
}
void GameEngine::sfmlDisplaySprites(void)
{
	for (uint16_t i = 0; i < spriteQueue.size(); i++)
		window->draw(spriteQueue[i]);
}

void GameEngine::sfmlLoadTexture(string fileName)
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
	}
	texture->setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	spriteQueue.push_back(sprite);
}

void GameEngine::sfmlDestroyTextures(void)
{
	for (uint16_t i = 0; i < spriteQueue.size(); i++)
		delete spriteQueue[i].getTexture();
}
