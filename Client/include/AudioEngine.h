#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H
#include <errno.h>
#include <string>
#include <thread>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

namespace engine
{
	class Audio
	{
	public:
		Audio(Audio const&) = delete;
		void operator=(Audio const&) = delete;
		static Audio& getInstance(void);
		void gruntPlay(uint16_t health);

	private:
		Audio();
		~Audio();

		std::vector<sf::Sound*> m_soundsGrunt;
	};
}
#endif