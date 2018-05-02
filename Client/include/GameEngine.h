#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <vector>
#include <string>
#include <thread>
#include <SFML/Graphics.hpp>
#include <mutex>
#include "MainPlayer.h"
#include "Map.h"
#include "Event.h"

namespace engine
{
	class Game
	{
	public:
		Game(uint16_t width, uint16_t height);
		~Game();
		void sfmlInit(void);
		bool sfmlCleanup(void);
		void sfmlRender(void);
		bool deleteSpriteFromQueue(sf::Sprite *o_sprite);
		void addSpriteToQueue(sf::Sprite *o_sprite);

		static sf::Texture *m_ennemy_texture;
		MainPlayer m_MainPlayer;
		uint16_t m_ennemiesCount;
		std::mutex m_mutex;

	private:
		void sfmlCreateWindow(void);
		void sfmlDisplaySprites(void);
		void sfmlLoadTexture(std::string fileName);
		void sfmlLoadPlayerTexture(std::string fileName);
		void sfmlLoadEnnemiesTexture(std::string fileName, uint16_t position);
		static void sfmlCreateEnnemyTexture(void);
		void EnnemiesPlayersUpdateState(void);
		void sfmlLoadAllTextures(void);
		void sfmlDestroyTextures(void);
		void drawWalls(void);
		void drawBullets(void);

		sf::RenderWindow *m_window;
		uint16_t m_width;
		uint16_t m_height;
		std::vector<sf::Sprite*> m_spriteQueue;
	};
}
#endif