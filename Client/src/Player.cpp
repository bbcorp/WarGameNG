#include "../include/Player.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Player::Player(void) : m_relativePos({ 0, 0, 32, 32 }), m_lastAnim(0), m_sprite({ 0, 0, 32, 32 }), m_walkAnimationStep(0), m_deathAnimationStep(0)
{

}

Player::Player(string name) : m_name(name), m_relativePos({ 0, 0, 32, 32 }), m_lastAnim(0), m_sprite({ 0, 0, 32, 32 }), m_walkAnimationStep(0), m_deathAnimationStep(0)
{

}

void Player::setName(string name)
{
	m_name = name;
}
void Player::displayName(void)
{
	cout << "name: " << m_name << endl;
}