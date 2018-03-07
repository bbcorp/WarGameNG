#include "../include/NetworkEngine.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
using asio::ip::udp;

engine::Network::Network(const string address) : m_receiver_endpoint(asio::ip::address::from_string(address), PORT)
{
	//m_socket.open(udp::v4());
}