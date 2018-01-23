#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SFML/Graphics.hpp>

class GameEngine
{
public:
	void sfmlInit(void);
	bool sfmlCleanup(void);
	void sfmlRender(void);

private:
	 void sfmlCreateWindow(void);

	 sf::RenderWindow *window;
	uint16_t width;
	uint16_t height;

};
#endif