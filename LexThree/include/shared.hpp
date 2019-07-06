#ifndef SHARED_HPP_INCLUDED
#define SHARED_HPP_INCLUDED

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

///a class for the communication between
class Shared
{
	public:
		Shared( sf::RenderWindow &window, sf::VideoMode &VideoMode, const std::string &configPath );
		~Shared();

		sf::RenderWindow &app;
		sf::VideoMode &videoMode;
		sf::Vector2u screenDim;

		boost::property_tree::ptree config;
};

#endif // SHARED_HPP_INCLUDED
