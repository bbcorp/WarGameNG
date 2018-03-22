#ifndef EVENT_H
#define EVENT_H
#include <SFML/Graphics.hpp>
#include "../include/MainPlayer.h"

namespace engine
{
	class Event
	{
	public:
		void handleEvents(sf::Window *window);
		void handleKeyboard(MainPlayer *o_MainPlayer);

	private:
		sf::Event m_event;
	};
}
#endif