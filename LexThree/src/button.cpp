#include "button.hpp"

#include <cmath>

#include "utility.hpp"

sf::Sound Button::sound;
sf::SoundBuffer Button::buffer;

bool Button::loadSound( const std::string &path )
{
	if( !buffer.loadFromFile( path ) )
		return false;
	sound.setBuffer( buffer );
	return true;
}

Button::Button( const std::string &label, sf::Font &font, unsigned int charSize, sf::Color col ) :
	m_time(0.f),
	m_isActive( false ),
	m_text( label, font, charSize )
{
	m_text.setColor( col );
	update();
}

Button::~Button()
{
}

void Button::setCharacterSize( unsigned int charSize )
{
	m_text.setCharacterSize( charSize );
	update();
}

void Button::setColor( sf::Color color )
{
	m_text.setColor( color );
}

void Button::setFont( const sf::Font &font )
{
	m_text.setFont( font );
	update();
}

void Button::setPosition( sf::Vector2f pos )
{
	m_text.setPosition( pos );
}
void Button::setString( const std::string &label )
{
	m_text.setString( label );
	update();
}

void Button::update()
{
	m_text.setOrigin( ut::floor( ut::getSize( m_text.getLocalBounds() ) / 2.f ) );
}

bool Button::handleEvent( const sf::Event &event, sf::Vector2f mousePos ) //true when pressed, else false
{
	if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left ) {
		if( m_text.getGlobalBounds().contains( mousePos ) ) {
			return true;
		}
	}

	if( event.type == sf::Event::MouseMoved ) {
		if( m_text.getGlobalBounds().contains( mousePos ) ) {
			if( !m_isActive ) {
				sound.play();
				m_isActive = true;
			}
		}
		else {
			if( m_isActive ) {
				m_text.setScale( 1.f, 1.f );
				m_time = 0.f;
				m_isActive = false;
			}
		}
	}
	return false;
}

void Button::update( float elapsedTime )
{
	if( m_isActive ) {
		m_time += elapsedTime;

		const float startTime = 0.4f;

		float scale = 1.f;
		if( m_time < startTime ) {
			scale = 1.f + ( 0.2f ) * m_time / startTime;
		}
		else {
			scale = 1.2f + 0.1f * std::sin( ( m_time - startTime ) * 3.f );
		}

		m_text.setScale( scale, scale );
	}
}

void Button::expose( sf::RenderTarget &target ) const
{
	target.draw( m_text );
}
