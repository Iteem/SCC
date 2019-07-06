#include "enemie.h"

sf::Texture Enemie::bubbleImage;

Enemie::Enemie(float YPosition, float speed, Direction direction)
: mySpeed(speed)
{
    bubble.setTexture(bubbleImage);
    //bubble.resize(40, 40);
    bubble.setOrigin(bubbleImage.getSize().x / 2, bubbleImage.getSize().y / 2);
    if(direction == FromRight)
    {
        bubble.setPosition( 800, YPosition );
        mySpeed *= -1;
    }
    else
    {
        bubble.setPosition( 0, YPosition);
    }
}

void Enemie::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(bubble);
}

void Enemie::update(float elapsedTime)
{
    bubble.move(mySpeed * elapsedTime, 0);
}
