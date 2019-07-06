#ifndef MENUSTATE_HPP_INCLUDED
#define MENUSTATE_HPP_INCLUDED

#include "state.hpp"
#include "comet.hpp"
#include "button.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

///class for the menu
class MenuState : public State
{
    public:
        MenuState(Shared &shared);
        virtual ~MenuState();

        virtual void init(void);     //load resources
        virtual void destroy(void);  //free resources

        virtual void pause(void);
        virtual void resume(void);

        virtual Next update(void);       //update the state, return the next state
        virtual void draw(void) const;   //draw everything
    private:
        sf::Image backgroundImage;
        sf::Sprite background;

        Comet cursor;

        sf::Font font;
        Button *startButton, *aboutButton, *exitButton;
        bool startPressed, aboutPressed, exitPressed;

        sf::Music music;
};

#endif // MENUSTATE_HPP_INCLUDED
