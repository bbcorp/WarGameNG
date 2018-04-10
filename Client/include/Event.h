#ifndef EVENT_H
#define EVENT_H
#include <SFML/Graphics.hpp>
#include <thread>
#include "../include/MainPlayer.h"

namespace engine
{
	class Event
	{
	public:
		Event(sf::RenderWindow *window, MainPlayer *o_MainPlayer);
		void handleEvents(void);
		void handleKeyboard(void);

	private:
		sf::Event m_event;
		sf::RenderWindow *m_window;
		MainPlayer *m_MainPlayer;
	};
}
#endif