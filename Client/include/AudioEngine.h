#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H
#include <errno.h>
#include <string>
#include <thread>
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
		bool gruntPlay(void);

	private:
		Audio();

		void gruntLoop(void);

		sf::SoundBuffer m_bufferGrunt;
		sf::Sound m_soundGrunt;
		sf::Time m_gruntOffset;
		std::thread *m_thread_grunt;
	};
}
#endif