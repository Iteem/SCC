#ifndef MENUSTATE_HPP_INCLUDED
#define MENUSTATE_HPP_INCLUDED

#include "state.hpp"

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "map.hpp"

///class for the menu
class MenuState : public State
{
	public:
		MenuState(Shared &shared);
		virtual ~MenuState();

		virtual bool init();	 //load resources
		virtual void destroy();  //free resources

		virtual void pause();
		virtual void resume();

		virtual Next update();  //update the state, return the next state
		virtual Next handleEvent( const sf::Event &event );  //handle a SFML-event
		virtual void draw() const; //draw everything

	private:
		Map m_mapBackground;

		sf::Font m_font;
		sf::Text m_title;

		std::shared_ptr<Button> m_startButton;
		std::shared_ptr<Button> m_optionsButton;
		std::shared_ptr<Button> m_exitButton;

		sf::Clock frameClock;
		float frameTime;
};

#endif // MENUSTATE_HPP_INCLUDED
