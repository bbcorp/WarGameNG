#include "../include/NetworkEngine.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
using asio::ip::udp;

engine::Network::Network(const string address) : m_receiver_endpoint(asio::ip::address::from_string(address), PORT)
{
	m_socket = new udp::socket(m_io_service);
	m_socket->open(udp::v4());
	//m_socket.open(udp::v4());
}

size_t engine::Network::sendData(std::string *send_buffer)
{
	return m_socket->send_to(asio::buffer(*send_buffer), m_receiver_endpoint);
}