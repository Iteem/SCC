#include "shared.hpp"

Shared::Shared(sf::RenderWindow &window, sf::VideoMode &VideoMode, Config &pConfig) :
app(window),
videoMode(VideoMode),
config(pConfig)
{
};

Shared::~Shared()
{
};

