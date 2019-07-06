#ifndef ENEMIEWEAPON_H
#define ENEMIEWEAPON_H

#include <SFML/Graphics.hpp>

#include "player.h"

class EnemieWeapon : public sf::Drawable
{
    public:
        EnemieWeapon(sf::Vector2f Pos, sf::Vector2f direction);
        ~EnemieWeapon(){};
        static bool init(void){return orangeBubbleImage.loadFromFile("data/bubble_orange.png");};
        void update(float elapsedTime);
        sf::Vector2f GetPos(void) const {return orangeBubble.getPosition();};
        bool coolide(const Player &player) const;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        static sf::Texture orangeBubbleImage;
        sf::Sprite orangeBubble;
        sf::Vector2f myDirection;
};

#endif // ENEMIEWEAPON_H
