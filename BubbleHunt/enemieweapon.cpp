#include "enemieweapon.h"

sf::Texture EnemieWeapon::orangeBubbleImage;

EnemieWeapon::EnemieWeapon(sf::Vector2f Pos, sf::Vector2f direction) :
myDirection(direction)
{
    orangeBubble.setTexture(orangeBubbleImage);
    //orangeBubble.Resize(10.f, 10.f);
    orangeBubble.setPosition(Pos);
    orangeBubble.setOrigin(orangeBubbleImage.getSize().x / 2, orangeBubbleImage.getSize().y / 2);
}

void EnemieWeapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(orangeBubble);
}

void EnemieWeapon::update(float elapsedTime)
{
    orangeBubble.move(myDirection* elapsedTime);
}

bool EnemieWeapon::coolide(const Player &player) const
{
    float x = player.getPos().x - orangeBubble.getPosition().x;
    float y = player.getPos().y - orangeBubble.getPosition().y;
    return 42.5*42.5 > x*x + y*y;
}
