#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../include/MainPlayer.h"

namespace engine
{
	class Game
	{
	public:
		Game(uint16_t width, uint16_t height);
		void sfmlInit(void);
		bool sfmlCleanup(void);
		void sfmlRender(void);
		MainPlayer m_MainPlayer;

	private:
		void sfmlCreateWindow(void);
		void sfmlDisplaySprites(void);
		void sfmlLoadTexture(std::string fileName);
		void sfmlLoadPlayerTexture(std::string fileName);
		void sfmlLoadAllTextures(void);
		void sfmlDestroyTextures(void);

		sf::RenderWindow *m_window;
		uint16_t m_width;
		uint16_t m_height;
		std::vector<sf::Sprite*> m_spriteQueue;
	};
}
#endif