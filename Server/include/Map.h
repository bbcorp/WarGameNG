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
		Map(Map const&) = delete;
		void operator=(Map const&) = delete;
		static Map& getInstance();
		static const std::vector<sf::FloatRect> getWalls(void);
		static sf::Vector2u getSpawn(void);
		static bool mapIntersection(sf::FloatRect *rect);

	private:
		Map();
		static void constructMapRects(void);
		std::vector<uint8_t> loadBmp(const std::string fileName);

		uint8_t *m_bmpPixelData;
		static std::vector<sf::FloatRect> m_walls;
	};
}
#endif