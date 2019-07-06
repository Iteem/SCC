#include "weapon.h"

sf::Texture Weapon::redBubbleImage;

const float Speed = 100.f;

Weapon::Weapon(sf::Vector2f Position)
{
    redBubble.setTexture(redBubbleImage);
    //redBubble.Resize(15.f, 15.f);
    redBubble.setPosition(Position);
    redBubble.setOrigin(redBubbleImage.getSize().x / 2, redBubbleImage.getSize().y / 2);
}

bool Weapon::coolide(const Enemie &enemie) const
{
    float x = enemie.GetPos().x - redBubble.getPosition().x;
    float y = enemie.GetPos().y - redBubble.getPosition().y;
    return 25*25 > x*x + y*y;
}

void Weapon::update(float elapsedTime)
{
    redBubble.move(0, Speed * elapsedTime);
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(redBubble);
}
