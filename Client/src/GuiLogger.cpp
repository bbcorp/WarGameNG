#include <iostream>
#include "../include/GuiLogger.h"
#include "../include/ft_Delay.h"

using namespace std;

engine::GuiLogger::GuiLogger() : m_show(false)
{
	if (!m_font.loadFromFile("../res/calibri.ttf"))
		return;
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::White);

}

void engine::GuiLogger::setMessage(const std::string message, bool messageType)
{
	if (messageType) // It's an error
		cerr << "[ERROR] " << message << endl;
	else
		cout << "[INFO] " << message << endl;
	m_text.setString(message);
	m_show = true;
	m_clock.restart();
}

void engine::GuiLogger::updatePosition(const sf::Vector2f position)
{
	m_text.setPosition(position);
}

engine::GuiLogger& engine::GuiLogger::getInstance(void)
{
	static GuiLogger instance;
	return instance;
}

const string engine::GuiLogger::getCurrentMessage(void)
{
	return m_text.getString();
}

const bool engine::GuiLogger::getShowBoolean(void)
{
	/* Inversed ft_delay without restart */
	if (m_clock.getElapsedTime() < sf::seconds(1.2))
		return true;
	else
		return false;
}

const sf::Text* engine::GuiLogger::getText(void) const
{
	return &m_text;
}