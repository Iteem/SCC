#include "shared.hpp"

Shared::Shared(sf::RenderWindow &window, sf::VideoMode &pVideoMode, Config &pConfig) :
app(window),
videoMode(pVideoMode),
config(pConfig)
{
};

Shared::~Shared()
{
};

