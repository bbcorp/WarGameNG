#include <stdlib.h>
#include <iostream>
#include "../include/GameEngine.h"
#include "../include/PlayerBase.h"

#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")

using namespace std;


int main(int argc, int *argv[])
{
	GameEngine gameEngine;
	PlayerBase pBase[2];
	pBase[0].receiveDamage(10);
	pBase[0].receiveDamage(10);
	pBase[0].displayName();
	pBase[1].receiveDamage(10);
	pBase[1].receiveDamage(10);
	pBase[1].receiveDamage(10);
	gameEngine.sfmlInit();
	gameEngine.sfmlRender();
	return EXIT_SUCCESS;
}
