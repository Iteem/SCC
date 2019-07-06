#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "object.hpp"
#include "shot.hpp"

#include <list>

class Enemy : public Object
{
    public:
        Enemy();
        virtual ~Enemy();

        virtual sf::FloatRect GetRect(void) const;
        void update(float elapsedTime, std::list<Shot *> &shotList);

        virtual void draw(sf::RenderTarget &target) const;
    private:
        sf::Sprite m_sprite;

        float m_timer;
};

#endif // ENEMY_HPP_INCLUDED
