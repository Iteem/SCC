#ifndef COMET_HPP_INCLUDED
#define COMET_HPP_INCLUDED

#include "tail.hpp"

class Comet : public sf::Drawable
{
    public:
        Comet(sf::Color color, float thickness, float lifetimeLimit = 0.1f);
        ~Comet();

        void update(float elapsedTime);
    private:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        Tail m_tail;
        sf::Shape m_circle;
        sf::Vector2f m_lastPosition;
};

#endif // COMET_HPP_INCLUDED
