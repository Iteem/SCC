#ifndef SHARED_HPP_INCLUDED
#define SHARED_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>

#include "audiomanager.hpp"
#include "config.hpp"

///a class for the communication between
class Shared
{
    public:
        Shared(sf::RenderWindow &window, sf::VideoMode &pVideoMode, Config &pConfig);
        ~Shared();

        sf::RenderWindow &app;
        sf::VideoMode &videoMode;
        Config &config;
        AudioManager audioManager;
};

#endif // SHARED_HPP_INCLUDED
