#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "enemie.h"

class Weapon : public sf::Drawable
{
    public:
        Weapon(sf::Vector2f Pos);
        ~Weapon(){};
        static bool init(void){return redBubbleImage.loadFromFile("data/bubble_red.png");};
        void update(float elapsedTime);
        float GetY(void) const {return redBubble.getPosition().y;};
        bool coolide(const Enemie &enemie) const;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        static sf::Texture redBubbleImage;
        sf::Sprite redBubble;
};

#endif // WEAPON_H
