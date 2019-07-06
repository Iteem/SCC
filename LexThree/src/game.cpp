#include "game.hpp"

#include <memory>

#include "menustate.hpp"
#include "gamestate.hpp"
#include "shared.hpp"
#include "state.hpp"

Game::Game(int argc, char **argv)
{
	exit = false;
}

Game::~Game()
{
}

int Game::run(void)
{
	//set up a window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;
	sf::VideoMode videoMode( 1024, 768, 32 );

	sf::RenderWindow app( videoMode, "LexThree", sf::Style::Default, settings );
	app.setFramerateLimit( 120 );
	//app.setVerticalSyncEnabled( true );

	//set up a state
	m_shared.reset( new Shared( app, videoMode, "data/game.ini" ) );
	m_state.reset( new MenuState( *m_shared ) );
	if( !m_state->init() )
		return 1;

	while( true ){
		sf::Event event;

		while( app.pollEvent( event ) ){
			handleSwap( m_state->handleEvent( event ) );
		}

		handleSwap( m_state->update() );

		if( exit )
			return 0;

		m_state->draw();

		app.display();
	}
}

void Game::handleSwap( State::Next next )
{
	//check if state change is necessary
	if(next != State::NoChange){
		m_state->destroy();

		//create and initialize an new state
		switch( next ){
			case State::Menu:
				m_state.reset( new MenuState( *m_shared ) );
				break;
			case State::Game:
				m_state.reset( new GameState( *m_shared ) );
				break;
			default:
				exit = true; //State::Quit or unknown state type, exit
				return;
		}
		exit = !m_state->init();
	}
}
