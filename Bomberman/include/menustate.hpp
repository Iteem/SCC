#ifndef MENUSTATE_HPP_INCLUDED
#define MENUSTATE_HPP_INCLUDED

#include "state.hpp"
#include <SFML/Graphics.hpp>

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
        sf::Image m_backgroundImage;
        sf::Sprite m_background;
        sf::Sprite m_logo;

        sf::Text m_startText;
        sf::Text m_helpText;
        sf::Text m_exitText;

        sf::Shape m_marker;

        int m_selected;
        bool m_displayHelp;

        sf::Sprite m_howto;
};

#endif // MENUSTATE_HPP_INCLUDED
