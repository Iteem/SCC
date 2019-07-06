#include "bomb.hpp"

#include "imagemanager.hpp"

const float Lifetime = 3.f;

Bomb::Bomb(sf::Vector2i pos) :
m_lifetime(0),
m_isExploded(false),
m_position(pos)
{
    m_sprite.SetImage(*IM.get("data/bomb.png"));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.f);
    m_sprite.Resize(20, 20);
    m_sprite.SetPosition(pos.x * 32 + 16, pos.y * 32 + 16);
}

Bomb::~Bomb()
{
}

void Bomb::update(float elapsedTime)
{
    m_lifetime += elapsedTime;
    if(m_lifetime > Lifetime)
        m_isExploded = true;
}

sf::Vector2i Bomb::getPosition() const
{
    return m_position;
}

bool Bomb::isExploded(void) const
{
    return m_isExploded;
}

void Bomb::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_sprite);
}
