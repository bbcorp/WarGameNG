#include <stdlib.h>
#include <iostream>
#include <string>
#include <asio.hpp>
#include "../../Client/include/protobuf_test.h"
#include "../include/NetworkEngine.h"
#define PORT 1977
#define MAX_LENGTH 4096

using namespace std;

int main(int argc, int *argv[])
{
	static engine::Network NetworkEngine;
	NetworkEngine.receiveLoop();
		
	return EXIT_SUCCESS;
}

