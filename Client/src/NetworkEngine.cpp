#include "../include/NetworkEngine.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
/*
void NetworkEngine::init(const char *address, SOCKADDR_IN *sin)
{
#ifdef _WIN32
	WSADATA WSAData;                    // Contains details of the 
										// Winsock implementation
										// Initialize Winsock. 
	try
	{
		if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
			throw true;
	}
	catch (bool const& networkErr)
	{
		cerr << "Can't initialize Network\n" << endl;
	}
#endif
	// UDP so SOCK_DGRAM

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct hostent *hostinfo;

	try
	{
		if (sock == INVALID_SOCKET)
			throw true;
		hostinfo = gethostbyname(address);
		if (hostinfo == NULL)
			throw true;

	}
	catch (bool const& networkErr)
	{
		cerr << "Can't initialize Network\n" << endl;
	}

	sin->sin_addr = *(IN_ADDR *)hostinfo->h_addr;
	sin->sin_port = htons(PORT);
}

bool NetworkEngine::connect(void)
{
	psin = new SOCKADDR_IN;
}

void NetworkEngine::clean(void)
{
	// Send quit message to server before cleanup
	// /!\ TODO PROTOBUF /!\ 
	uint8_t bufferQuit[QuitMessage_size];
	QuitMessage qMessage;
	qMessage.id = _engine.mainPlayer.playerBase.id;
	pb_ostream_t outputQuit = pb_ostream_from_buffer(bufferQuit, sizeof(bufferQuit));
	if (encode_unionmessage(&outputQuit, QuitMessage_fields, &qMessage))
		write_client(bufferQuit, outputQuit.bytes_written);
#ifdef WIN32
	WSACleanup();
#endif
	closesocket(sock);
}

int64_t NetworkEngine::readClient(const std::string *readBuffer)
{
	int64_t n = 0;
	size_t sinsize = sizeof(*psin);
	if ((n = recvfrom(sock, readBuffer, MAX_BUFFER, 0, (SOCKADDR *)psin, &sinsize)) < 0)
	{
		perror("recvfrom()");
		return RECVERROR;
	}
	return n;
}

int64_t NetworkEngine::writeClient(const std::string *writeBuffer, const int64_t length)
{

}*/