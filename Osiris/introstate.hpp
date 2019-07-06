#ifndef INTROSTATE_HPP_INCLUDED
#define INTROSTATE_HPP_INCLUDED

#include "state.hpp"
#include "comet.hpp"
#include "texturedshape.hpp"

#include <SFML/Graphics.hpp>

class IntroState : public State
{
    public:
        IntroState(Shared &shared);
        virtual ~IntroState();

        virtual void init(void);     //load resources
        virtual void destroy(void);  //free resources

        virtual void pause(void);
        virtual void resume(void);

        virtual Next update(void);       //update the state, return the next state
        virtual void draw(void) const;   //draw everything
    private:
        sf::Image im;
        TexturedShape ts;
        Comet cursor;
        float time;

        sf::Font papyrus;

        sf::Text text1;
        sf::Text text2;
};

#endif // INTROSTATE_HPP_INCLUDED
