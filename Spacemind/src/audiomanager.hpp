#ifndef AUDIOMANAGER_HPP_INCLUDED
#define AUDIOMANAGER_HPP_INCLUDED

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class AudioManager
{
	public:
		AudioManager();
		~AudioManager();

		bool loadListFromFile(const std::string &path);

		bool isLoaded();
		bool isPlaying();

		void play();
		void stop();
	private:
		std::vector<std::string> m_paths;
		std::string m_basepath;

		size_t m_index;
		sf::Music m_music;

		sf::Thread m_thread;
		bool m_isPlaying;

		void run();
};

#endif // AUDIOMANAGER_HPP_INCLUDED
