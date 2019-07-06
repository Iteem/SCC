#include "audiomanager.hpp"

#include <fstream>
#include <iostream>

AudioManager::AudioManager() :
m_index(0),
m_thread(&AudioManager::run, this),
m_isPlaying(false)
{

}

AudioManager::~AudioManager()
{
	stop();
}

bool AudioManager::loadListFromFile(const std::string &path)
{
	stop();
	m_paths.clear();

    std::ifstream file(path.c_str());
    if(!file.good()){
        std::cerr << "Failed to open file \"" << path << "\"." << std::endl;
        return false;
    }

	//set basepath
	size_t pos = path.rfind('/');
    if(pos == std::string::npos){
        m_basepath = "./";
    } else {
    	m_basepath = (path.substr(0, pos+1));
    }


	std::string str;
	while(file.good()){
		std::getline(file, str);

		m_paths.push_back(str);
	}
	return true;
}

bool AudioManager::isLoaded()
{
	return !m_paths.empty();
}

bool AudioManager::isPlaying()
{
	return m_isPlaying;
}

void AudioManager::play()
{
	if(!m_isPlaying){ //make sure thread is not already running
		m_isPlaying = true;
		m_thread.Launch();
	}
}

void AudioManager::stop()
{
	if(m_isPlaying){
		m_isPlaying = false;
		m_thread.Wait();
	}
}

void AudioManager::run()
{
	if(m_paths.empty()){
		m_isPlaying = false;
		std::cerr << "Warning: No music found." << std::endl;
		return;
	}

	//as long as not stopped go through the list over and over
	while(m_isPlaying){
		if(m_music.GetStatus() == sf::Music::Stopped){
			if(m_index >= m_paths.size())
				m_index = 0;

			if(!m_music.OpenFromFile(m_basepath + m_paths[m_index])){
				m_isPlaying = false;
				std::cerr << "Failed to open file \"" << m_basepath + m_paths[m_index] << "\"." << std::endl;
				std::cerr << "Shutting down the AudioManger." << std::endl;
				return;
			}

			m_music.Play();

			//for the next time take the next music
			m_index++;
		}

		//the thread doesn't need to be updated very often
		sf::Sleep(50);
	}

	//stop the music is necessary
	m_music.Stop();
}
