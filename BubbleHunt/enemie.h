#ifndef ENEMIE_H
#define ENEMIE_H

#include <SFML/Graphics.hpp>

enum Direction
{
    FromLeft,
    FromRight
};

class Enemie : public sf::Drawable
{
    public:
        Enemie(float XPosition, float Speed, Direction direction);
        ~Enemie(){};
        void update(float elapsedTime);
        sf::Vector2f GetPos(void) const {return bubble.getPosition();};
        static bool init(){return bubbleImage.loadFromFile("data/bubble.png");};
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        float mySpeed;
        static sf::Texture bubbleImage;
        sf::Sprite bubble;
};

#endif // ENEMIE_H
