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
		/*Game(uint16_t width, uint16_t height);
		void sfmlInit(void);
		bool sfmlCleanup(void);
		void sfmlRender(void);
		void sfmlLoadAllTextures(void);
		void sfmlLoadPlayerTexture(MainPlayer const o_MainPlayer, std::string filename);*/

	private:
		sf::Event m_event;
		/*void sfmlCreateWindow(void);
		void sfmlDisplaySprites(void);
		void sfmlLoadTexture(std::string fileName);
		void sfmlDestroyTextures(void);

		sf::RenderWindow *m_window;
		uint16_t m_width;
		uint16_t m_height;
		std::vector<sf::Sprite> m_spriteQueue;*/
	};
}
#endif