#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include "PlayerBase.h"
#include "Map.h"

class Player : public PlayerBase
{
public:
	Player();
	Player(std::string name);
	Player(const WarGame::fb::playerBase *pBase);
	~Player();
	void updateState(void);
	void applyModificationFromNetwork(Player *o_player);

	sf::Sprite m_sprite;
	sf::Clock m_clockUpdate;

private:
	
	int32_t m_lastAnim;
	int16_t m_walkAnimationStep;
	int16_t m_deathAnimationStep;
};

#endif