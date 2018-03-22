#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "PlayerBase.h"

class MainPlayer : public PlayerBase
{
public:
	MainPlayer(void);
	MainPlayer(std::string name);
	void updateOrientation(void);
	void move(int16_t x, int16_t y);

	sf::Sprite m_sprite;
private:
	int32_t m_lastAnim;
	int16_t m_walkAnimationStep;
	int16_t m_deathAnimationStep;
};

#endif