#include "menuState.hpp"

#include <Thor/Math.hpp>

#include "utility.hpp"

MenuState::MenuState(Shared &shared) :
State(shared)
{
}

MenuState::~MenuState()
{
}

bool MenuState::init()
{
	sf::Vector2f dim( m_shared.screenDim );

	// map
	if( !m_mapBackground.load( m_shared.config.get( "menu.map", "" ) ) )
		return false;
	m_mapBackground.update( sf::Vector2f( 1024/2, 768/2 ) );

	// title
	if( !m_font.loadFromFile( m_shared.config.get( "menu.font", "" ) ) )
		return false;
	m_title.setFont( m_font );
	m_title.setCharacterSize( m_shared.config.get( "menu.titlesize", 70 ) );
	m_title.setColor( sf::Color::Black );
	m_title.setString(  m_shared.config.get( "menu.title", "LexThree" ) );
	m_title.setOrigin( ut::floor( ut::getSize( m_title.getLocalBounds() ) / 2.f ) );
	m_title.setPosition( sf::Vector2f( 1024 / 2, 180 ) );

	//buttons
	if( !Button::loadSound( m_shared.config.get( "menu.buttonsound", "" ) ) )
		return false;

	m_startButton.reset( new Button( "Start", m_font, 50, sf::Color::Black ) );
	m_startButton->setPosition( sf::Vector2f( 1024 / 2, 380 ) );
	m_optionsButton.reset( new Button( "Options", m_font, 50, sf::Color::Black ) );
	m_optionsButton->setPosition( sf::Vector2f( 1024 / 2, 470 ) );
	m_exitButton.reset( new Button( "Quit", m_font, 50, sf::Color::Black ) );
	m_exitButton->setPosition( sf::Vector2f( 1024 / 2, 560 ) );

	// could have taken some time, better restart the clock
	frameClock.restart();

	return true;
}

void MenuState::destroy()
{
}

void MenuState::pause()
{
}

void MenuState::resume()
{
}

State::Next MenuState::update()
{
	sf::Time elapsedTime = frameClock.getElapsedTime();
	frameClock.restart();

	m_startButton->update( elapsedTime.asSeconds() );
	m_optionsButton->update( elapsedTime.asSeconds() );
	m_exitButton->update( elapsedTime.asSeconds() );

	return State::NoChange;
}

State::Next MenuState::handleEvent( const sf::Event &event )
{
	if( event.type == sf::Event::Closed )
		return State::Quit;

	sf::Vector2f mousePos = app.mapPixelToCoords( sf::Mouse::getPosition( app ) );

	if( m_startButton->handleEvent( event, mousePos ) )
		return State::Game;
	m_optionsButton->handleEvent( event, mousePos );
	if( m_exitButton->handleEvent( event, mousePos ) )
		return State::Quit;

	return State::NoChange;
}

void MenuState::draw() const
{
	app.clear();

	m_mapBackground.draw( app );

	app.draw( m_title );

	m_startButton->expose( app );
	m_optionsButton->expose( app );
	m_exitButton->expose( app );
}
