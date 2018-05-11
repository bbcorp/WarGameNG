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

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../include/NetworkEngine.h"
#include "../include/AudioEngine.h"

#ifdef _MSC_VER
	#ifdef _DEBUG
		#pragma comment(lib,"sfml-graphics-d.lib")
		#pragma comment(lib,"sfml-window-d.lib")
		#pragma comment(lib,"sfml-system-d.lib")
		#pragma comment(lib,"sfml-audio-d.lib")
	#else
		#pragma comment(lib,"sfml-graphics.lib")
		#pragma comment(lib,"sfml-window.lib")
		#pragma comment(lib,"sfml-system.lib")
		#pragma comment(lib,"sfml-audio.lib")
	#endif // _DEBUG
#endif // _MSC_VER

using namespace std;


int main(int argc, char *argv[])
{
	engine::Network::getInstance("localhost", &engine::Game::getInstance());
	engine::Game::getInstance().sfmlRender();
	
	return EXIT_SUCCESS;
}
