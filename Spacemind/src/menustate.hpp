#ifndef MENUSTATE_HPP_INCLUDED
#define MENUSTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "audiomanager.hpp"
#include "button.hpp"
#include "state.hpp"

///class for the menu
class MenuState : public State
{
    public:
        MenuState(Shared &shared);
        virtual ~MenuState();

        virtual bool init(void);     //load resources
        virtual void destroy(void);  //free resources

        virtual Next update(void);       //update the state, return the next state
        virtual void draw(void) const;   //draw everything
    private:
		sf::Sprite m_background;
		sf::Text m_title;

		Button *m_exitButton;
		bool m_exitButtonPressed;
		Button *m_startButton;
		bool m_startButtonPressed;
		Button *m_optionsButton;
		bool m_optionsButtonPressed;
};

#endif // MENUSTATE_HPP_INCLUDED
