#ifndef FT_DELAY_H
#define FT_DELAY_H
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace engine
{
	bool ft_Delay(sf::Clock *clock, sf::Time sleepTimeAnim);
}
#endif