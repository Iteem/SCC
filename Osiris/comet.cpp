#include "comet.hpp"

Comet::Comet(sf::Color color, float thickness, float lifetimeLimit) :
m_tail(color, thickness, lifetimeLimit),
m_circle(sf::Shape::Circle(0, 0, thickness / 2, color)),
m_lastPosition(0, 0)
{
}

Comet::~Comet()
{
}

void Comet::update(float elapsedTime)
{
    m_tail.update(elapsedTime, m_lastPosition - GetPosition());
    m_lastPosition = GetPosition();
}

void Comet::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_tail);
    target.Draw(m_circle);
}
