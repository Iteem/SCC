#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <utility>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace ut
{

template <typename T>
sf::Vector2<T> getSize( const sf::Rect<T> &rect )
{
	return sf::Vector2<T>( rect.width, rect.height );
}

template < typename T >
sf::Vector2<T> floor( const sf::Vector2<T> &vec )
{
	return sf::Vector2<T>( std::floor( vec.x ), std::floor( vec.y ) );
}

sf::Image createBubbleImage( unsigned int radius, sf::Color color, unsigned int border = 2, sf::Color borderColor = sf::Color::White );
sf::Image createBubbleImageBresenham( unsigned int radius, sf::Color color, unsigned int border = 2, sf::Color borderColor = sf::Color::White );

} //namespace ut


#endif // UTILITY_INCLUDED

