#include "../include/MainPlayer.h"
#include "pch.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

MainPlayer::MainPlayer(string name) : PlayerBase(name), m_relativePos(m_pos)/*, m_relativePos({ 0, 0, 32, 32 })*/, m_lastAnim(0), m_sprite({ 0, 0, 32, 32 }), m_walkAnimationStep(0), m_deathAnimationStep(0)
{

}
