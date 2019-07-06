#ifndef SHARED_HPP_INCLUDED
#define SHARED_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include "config.hpp"

///a class for the communication between
class Shared
{
    public:
        Shared(sf::RenderWindow &window, sf::VideoMode &VideoMode, Config &pConfig);
        ~Shared();

        sf::RenderWindow &app;
        sf::VideoMode &videoMode;
        Config &config;
};

#endif // SHARED_HPP_INCLUDED
