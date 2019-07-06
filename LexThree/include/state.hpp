#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "shared.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

///virtual base class for all states
class State
{
	public:
		enum Next
		{
			NoChange,
			Menu,
			Game,
			Quit
		};

		State(Shared &shared): m_shared(shared), app(shared.app){};
		virtual ~State(){};

		virtual bool init() = 0;	 //load resources
		virtual void destroy() = 0;  //free resources

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual Next update() = 0;  //update the state, return the next state
		virtual Next handleEvent( const sf::Event &event ) = 0;  //handle a SFML-event
		virtual void draw() const = 0; //draw everything

	protected:
		Shared &m_shared;
		sf::RenderWindow &app;
};

#endif // STATE_HPP_INCLUDED
