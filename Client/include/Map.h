#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace engine
{
	class Map
	{
	public:
		Map();
		Map(const std::string name);
		static const std::vector<sf::FloatRect> getWalls(void);
		static void constructMapRects(void);
		static bool mapIntersection(sf::FloatRect *rect);

	private:
		std::vector<uint8_t> loadBmp(const std::string fileName);

		uint8_t *m_bmpPixelData;
		static std::vector<sf::FloatRect> m_walls;
	};
}
#endif