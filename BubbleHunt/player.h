#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
    public:
        Player();
        ~Player(){};
        void update(float elapsedTime, float mouseX);
        sf::Vector2f getPos(void) const {return bubble.getPosition();};
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Image bubbleImage;
        sf::Sprite bubble;
        float timer;
};

#endif // PLAYER_H
