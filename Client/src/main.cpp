#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../include/GameEngine.h"
#include "../include/MainPlayer.h"
#include "../include/sprite.h"



#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")
#endif

using namespace std;


int main(int argc, int *argv[])
{
	static engine::Game EngineGame((uint16_t) 800, (uint16_t) 600);
	MainPlayer o_MainPlayer("bbcorp");
	o_MainPlayer.m_name.length();
	//o_MainPlayer.displayName2();
	//Player Players[2];
	//Players[0].displayName;
	/*NetworkEngine networkEngine;
	pBase[0].receiveDamage(10);
	pBase[0].receiveDamage(10);
	pBase[0].displayName();
	pBase[1].receiveDamage(10);
	pBase[1].receiveDamage(10);
	pBase[1].receiveDamage(10);*/
	EngineGame.sfmlRender();


	return EXIT_SUCCESS;
}
