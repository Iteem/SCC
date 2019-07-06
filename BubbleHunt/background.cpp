#include "background.h"

Background::Background(void)
{
    //create a shape looks like water
    water.append( sf::Vertex( sf::Vector2f(   0, 200 ), sf::Color(112, 141, 220) ) );
    water.append( sf::Vertex( sf::Vector2f( 800, 200 ), sf::Color(112, 141, 220) ) );
    water.append( sf::Vertex( sf::Vector2f( 800, 600 ), sf::Color( 37,  53, 150) ) );
    water.append( sf::Vertex( sf::Vector2f(   0, 600 ), sf::Color( 37,  53, 150) ) );

    //and one looks like a evening sky
    sky.append( sf::Vertex( sf::Vector2f(   0,   0 ), sf::Color( 22,  13,  18) ) );
    sky.append( sf::Vertex( sf::Vector2f( 800,   0 ), sf::Color( 22,  13,  18) ) );
    sky.append( sf::Vertex( sf::Vector2f( 800, 200 ), sf::Color(239,  82,  31) ) );
    sky.append( sf::Vertex( sf::Vector2f(   0, 200 ), sf::Color(239,  82,  31) ) );
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sky);
    target.draw(water);
}
