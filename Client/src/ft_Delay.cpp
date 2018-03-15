#include "../include/ft_Delay.h"

bool engine::ft_Delay(sf::Clock *clock, sf::Time sleepTimeAnim)
{
	if (clock->getElapsedTime() < sleepTimeAnim)
	{
		return false;
	}
	else
	{
		clock->restart();
		return true;
	}
}