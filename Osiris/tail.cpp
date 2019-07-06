#include "tail.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

Tail::Tail(sf::Color color, float thickness, float lifetimeLimit) :
m_color(color),
m_thickness(thickness),
m_lifetimeLimit(lifetimeLimit)
{
}

Tail::~Tail()
{
}

void Tail::update(float elapsedTime, sf::Vector2f delta)
{
    for(std::list< Joint >::iterator it = m_joints.begin(); it != m_joints.end();){
        it->m_position += delta;
        it->m_lifetime += elapsedTime;

        if(it->m_lifetime > m_lifetimeLimit){
            it = m_joints.erase(it);
        } else {
            ++it;
        }
    }

    if(std::abs(delta.x) > 0.01f or std::abs(delta.y) > 0.01f){
        Joint tmp;
        tmp.m_lifetime = 0.f;
        tmp.m_position = sf::Vector2f(0, 0);
        m_joints.push_back(tmp);
    }
}

void Tail::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    renderer.SetTexture(NULL);
    renderer.Begin(sf::Renderer::TriangleStrip);

    renderer.AddVertex((++m_joints.begin())->m_position.x, (++m_joints.begin())->m_position.y, m_color);
    for(std::list< Joint >::const_iterator it = (++m_joints.begin()); it != m_joints.end()--; ++it){
        std::list< Joint >::const_iterator it2 = it;
        it2--;
        sf::Vector2f normal(it2->m_position.y-it->m_position.y, it->m_position.x-it2->m_position.x);
        float k = 1.f / std::sqrt(normal.x * normal.x + normal.y * normal.y);
        normal *= k * m_thickness * 0.5f * (1.f - it->m_lifetime/m_lifetimeLimit);

        renderer.AddVertex(it->m_position.x+normal.x, it->m_position.y+normal.y, m_color);
        renderer.AddVertex(it->m_position.x-normal.x, it->m_position.y-normal.y, m_color);
    }

    renderer.End();
}
