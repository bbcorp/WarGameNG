#include "../include/AudioEngine.h"

using namespace std;

engine::Audio::Audio() : m_gruntOffset(sf::seconds(0)), m_thread_grunt(nullptr)
{
	if (!m_bufferGrunt.loadFromFile("../res/grunt.ogg"))
		exit(EXIT_FAILURE);
	m_soundGrunt.setBuffer(m_bufferGrunt);
}

engine::Audio& engine::Audio::getInstance(void)
{
	static Audio instance;
	return instance;
}

bool engine::Audio::gruntPlay(void)
{
	if (m_gruntOffset > sf::seconds(0))
		m_soundGrunt.setPlayingOffset(m_gruntOffset);
	m_soundGrunt.play();
	if (m_thread_grunt == nullptr)
	{
		m_thread_grunt = new thread(&engine::Audio::gruntLoop, this);
		return true;
	}
	else
		return false;

}

void engine::Audio::gruntLoop(void)
{
	while (m_soundGrunt.getPlayingOffset() < m_gruntOffset + sf::seconds(1))
	{
		this_thread::sleep_for(50ms);
	}
	m_soundGrunt.stop();
	if (m_gruntOffset < sf::seconds(4))
		m_gruntOffset += sf::seconds(1);
	else
		m_gruntOffset = sf::seconds(0);
	m_thread_grunt = nullptr;
}