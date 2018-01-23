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
	return true;
}

void GameEngine::sfmlCreateWindow(void)
{
	width = 800;
	height = 600;
	window = new sf::RenderWindow(sf::VideoMode(800, 600), " My Window");
	window->setVerticalSyncEnabled(true);
}

void GameEngine::sfmlRender(void)
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}
}
