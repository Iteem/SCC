#include "explosion.hpp"

#include "imagemanager.hpp"

const float Lifetime = 1.f;

Explosion::Explosion(sf::Vector2i pos) :
m_lifetime(0),
m_isDead(false),
m_position(pos)
{
    m_sprite.SetImage(*IM.get("data/explosion.png"));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.f);
    m_sprite.Resize(32, 32);
    m_sprite.SetPosition(pos.x * 32 + 16, pos.y * 32 + 16);
}

Explosion::~Explosion()
{
}

void Explosion::update(float elapsedTime)
{
    m_lifetime += elapsedTime;
    if(m_lifetime > Lifetime)
        m_isDead = true;
}

sf::Vector2i Explosion::getPosition() const
{
    return m_position;
}

bool Explosion::isDead(void) const
{
    return m_isDead;
}

void Explosion::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_sprite);
}
