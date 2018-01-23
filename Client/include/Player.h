#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Rect.hpp>
#include <string>

class Player
{
public:
	Player(void);
	Player(std::string name);
	void setName(std::string name);
	void displayName(void);
private:
	std::string m_name;
	sf::IntRect m_relativePos;
	int32_t m_lastAnim;
	sf::IntRect m_sprite;
	int16_t m_walkAnimationStep;
	int16_t m_deathAnimationStep;
};

#endif