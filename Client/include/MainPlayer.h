#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "PlayerBase.h"

class MainPlayer : public PlayerBase
{
public:
	MainPlayer(std::string name);
private:
	sf::IntRect m_relativePos;
	int32_t m_lastAnim;
	sf::IntRect m_sprite;
	int16_t m_walkAnimationStep;
	int16_t m_deathAnimationStep;
};

#endif