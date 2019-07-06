#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "shared.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

///virtual base class for all states
class State
{
    public:
        enum Next
        {
            NoChange,
            Intro,
            Menu,
            Game,
            Quit
        };

        State(Shared &shared): m_shared(shared), app(shared.app){};
        virtual ~State(){};

        virtual void init(void) = 0;     //load resources
        virtual void destroy(void) = 0;  //free resources

        virtual void pause(void) = 0;
        virtual void resume(void) = 0;

        virtual Next update(void) = 0;       //update the state, return the next state
        virtual void draw(void) const = 0;   //draw everything

    protected:
        Shared &m_shared;
        sf::RenderWindow &app;
};

#endif // STATE_HPP_INCLUDED
