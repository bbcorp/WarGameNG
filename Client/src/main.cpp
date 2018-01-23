#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../include/GameEngine.h"
#include "../include/PlayerBase.h"
#define ASIO_STANDALONE
#include <asio.hpp>


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
	asio::io_service io_service;
	asio::ip::udp::resolver resolver(io_service);
	asio::ip::udp::resolver::query query(asio::ip::udp::v4(), "127.0.0.1", "daytime");
	asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
	asio::ip::udp::socket socket(io_service);
	socket.open(asio::ip::udp::v4());
	vector<char> send_buffer(1);
	send_buffer[0] = { 0 };
	socket.send_to(asio::buffer(send_buffer), receiver_endpoint);



	return EXIT_SUCCESS;
}
