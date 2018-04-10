#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include "PlayerBase.h"

typedef enum e_wallPosition
{
	WALL_NONE = 0,
	WALL_LEFTRIGHT = 1,
	WALL_UPDOWN = 2,
	WALL_BOTH = 3
} t_wallPosition;

class MainPlayer : public PlayerBase
{
public:
	MainPlayer(void);
	MainPlayer(std::string name);
	MainPlayer(const WarGame::fb::playerBase *pBase);
	virtual ~MainPlayer();
	void updateState(void);
	void applyModificationFromNetwork(MainPlayer *o_player);
	void move(int16_t x, int16_t y);

	sf::Sprite m_sprite;
	sf::View m_PlayerView;
	sf::Clock *m_clockUpdate;
private:
	void nearWallMode(int16_t x, int16_t y);
	
	sf::FloatRect m_PlayerViewRect;
	sf::Texture *m_ennemy_texture;
	std::vector<sf::FloatRect> m_wallRects;
	int32_t m_lastAnim;
	int16_t m_walkAnimationStep;
	int16_t m_deathAnimationStep;
};

#endif