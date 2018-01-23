#include "../include/PlayerBase.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


PlayerBase::PlayerBase() : m_id(-1), m_health((uint16_t)100), m_ammo((uint16_t)30), m_state((uint16_t)0), m_orientation((uint16_t)0), m_pos({ 0, 0, 32, 32 })
{

}

PlayerBase::PlayerBase(string name) : Player(name), m_name(name), m_id(-1), m_health((uint16_t)100), m_ammo((uint16_t)30), m_state((uint16_t)0), m_orientation((uint16_t)0), m_pos({ 0, 0, 32, 32 })
{

}

void PlayerBase::receiveDamage(uint16_t damage)
{
	if (m_health > 0)
		m_health -= damage;
	cout << m_health << endl;
}
void PlayerBase::displayName2(void)
{
	cout << "name: " << m_name << endl;
}