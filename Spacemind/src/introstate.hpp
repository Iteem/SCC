#ifndef INTROSTATE_HPP_INCLUDED
#define INTROSTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "state.hpp"

class IntroState : public State
{
    public:
        IntroState(Shared &shared);
        virtual ~IntroState();

        virtual bool init(void);     //load resources
        virtual void destroy(void);  //free resources

        virtual Next update(void);       //update the state, return the next state
        virtual void draw(void) const;   //draw everything
    private:
		sf::Texture texLogo, texWheel;
		sf::Sprite logo, wheel;

		unsigned int time;
};

#endif // INTROSTATE_HPP_INCLUDED
