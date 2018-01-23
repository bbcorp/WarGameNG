#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class GameEngine
{
public:
	void sfmlInit(void);
	bool sfmlCleanup(void);
	void sfmlRender(void);

private:
	 void sfmlCreateWindow(void);
	 void sfmlDisplaySprites(void);
	 void sfmlLoadTexture(std::string fileName);
	 void sfmlDestroyTextures(void);

	sf::RenderWindow *window;
	uint16_t width;
	uint16_t height;
	std::vector<sf::Sprite> spriteQueue;

};
#endif