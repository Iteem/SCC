#include "normalshot.hpp"

NormalShot::NormalShot(sf::Image const* image, sf::Vector2f pos, sf::Vector2f velocity, sf::Vector2f size) :
m_velocity(velocity)
{
    m_sprite.SetImage(*image);
    m_sprite.SetPosition(pos);
    m_sprite.SetOrigin(image->GetWidth()/2, image->GetHeight()/2);
    m_sprite.Resize(size);
}

NormalShot::~NormalShot()
{
}

sf::FloatRect NormalShot::GetRect(void) const
{
    sf::Vector2f leftCorner(m_sprite.GetPosition().x - m_sprite.GetOrigin().x * m_sprite.GetScale().x,
                            m_sprite.GetPosition().y - m_sprite.GetOrigin().y * m_sprite.GetScale().y);
    return sf::FloatRect(leftCorner, m_sprite.GetSize());
}

void NormalShot::update(float elapsedTime)
{
    m_sprite.Move(m_velocity * elapsedTime);
    if(m_sprite.GetPosition().x < 192 or m_sprite.GetPosition().x > 832 or
       m_sprite.GetPosition().y < 0 or m_sprite.GetPosition().y > 768){
        remove = true;
    }

}

void NormalShot::draw(sf::RenderTarget &target) const
{
    target.Draw(m_sprite);
}
