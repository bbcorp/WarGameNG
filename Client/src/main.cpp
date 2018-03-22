#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../include/GameEngine.h"
#include "../include/NetworkEngine.h"
#include "../include/MainPlayer.h"
#include "../include/sprite.h"
#include "../include/protobuf_test.h"



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
	static engine::Network EngineNetwork("127.0.0.1", &EngineGame);
	
	/*if (typeid(a).hash_code() == typeid(MainPlayer).hash_code())
	{
		 It's a MainPlayer class/Object
		bool mainplayer = true;
	}*/

	EngineGame.sfmlRender();


	return EXIT_SUCCESS;
}
