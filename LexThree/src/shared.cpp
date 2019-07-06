#include "shared.hpp"

#include <boost/property_tree/ini_parser.hpp>

Shared::Shared( sf::RenderWindow &window, sf::VideoMode &VideoMode, const std::string &configPath ) :
app(window),
videoMode(VideoMode)
{
	screenDim = sf::Vector2u( VideoMode.width, VideoMode.height );

	read_ini( configPath, config );
}

Shared::~Shared()
{
}

