#ifndef SHARED_HPP_INCLUDED
#define SHARED_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>

///a class for the communication between
class Shared
{
    public:
        Shared(sf::RenderWindow &window, sf::VideoMode &VideoMode);
        ~Shared();

        sf::RenderWindow &app;
        sf::VideoMode &videoMode;
};

#endif // SHARED_HPP_INCLUDED
