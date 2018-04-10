#ifndef MAP_H
#define MAP_H
#include <string>
#include <SFML/Graphics.hpp>
#include "../include/MainPlayer.h"

namespace engine
{
	class Map
	{
	public:
		Map(const std::string name);

	private:
		void loadBmp(const std::string fileName);

		uint8_t *m_bmpPixelData;
	};
}
#endif