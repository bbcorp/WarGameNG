#include "../include/MainPlayer.h"
#include <stdlib.h>
#include <iostream>
#include "../include/ft_Delay.h"
#include "../include/sprite.h"

using namespace std;

MainPlayer::MainPlayer() : PlayerBase(), m_lastAnim(0), m_walkAnimationStep(0), m_deathAnimationStep(0)
{
	m_sprite.setTextureRect({ 1, 1, 32, 32 });
	m_sprite.setPosition({ 384.0, 284.0 });
}

MainPlayer::MainPlayer(string name) : PlayerBase(name), m_lastAnim(0),  m_walkAnimationStep(0), m_deathAnimationStep(0)
{
	m_sprite.setTextureRect({ 1, 1, 32, 32 });
	m_sprite.setPosition({ 384.0, 284.0 });
}

void MainPlayer::updateOrientation(void)
{
	if (m_state == WALK)
	{
		sf::Clock clock;
		engine::ft_Delay(&clock, sf::milliseconds(150));
	}
	m_sprite.setTextureRect({ 1, m_orientation * 32 + m_orientation * 1 + 1, 32, 32 });
}

void MainPlayer::move(int16_t x, int16_t y)
{
	m_sprite.move(x, y);
	m_pos.x = +x;
	m_pos.y = +y;
}