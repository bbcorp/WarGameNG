#include "../include/AudioEngine.h"

using namespace std;

engine::Audio::Audio()
{
	sf::SoundBuffer *soundBuffer = nullptr;
	sf::Sound *sound = nullptr;
	for (uint16_t i = 1; i <= 5; i++)
	{
		if (soundBuffer != nullptr || sound != nullptr)
			exit(EXIT_FAILURE);
		soundBuffer = new sf::SoundBuffer;
		if (!soundBuffer->loadFromFile("../res/audio/grunt/grunt0" + to_string(i) + ".ogg"))
			exit(EXIT_FAILURE);
		sf::Sound *sound = new sf::Sound(*soundBuffer);
		m_soundsGrunt.push_back(sound);
		sound = nullptr;
		soundBuffer = nullptr;
	}
}

engine::Audio::~Audio()
{
	for (sf::Sound *sound : m_soundsGrunt)
	{
		delete sound->getBuffer();
		delete sound;
	}
}

engine::Audio& engine::Audio::getInstance(void)
{
	static Audio instance;
	return instance;
}

void engine::Audio::gruntPlay(uint16_t health)
{
	uint16_t i = (1 - (float(health) / 100)) * 4;
	m_soundsGrunt[i]->play();
}