#include "ship.hpp"
#include "normalshot.hpp"

Ship::Ship()
{
    m_shipImage.LoadFromFile("data/ship.png");

    m_sprite.SetImage(m_shipImage);
    m_sprite.SetOrigin(m_shipImage.GetWidth()/2, m_shipImage.GetHeight()/2);
    m_sprite.Resize(0, 50);
    m_sprite.SetScaleX(m_sprite.GetScale().y);

    shotImage = new sf::Image;
    shotImage->LoadFromFile("data/shot.png");

    m_timer = 0;
}

Ship::~Ship()
{
    delete shotImage;
}

sf::FloatRect Ship::GetRect(void) const
{
    sf::Vector2f leftCorner(m_sprite.GetPosition().x - m_sprite.GetOrigin().x * m_sprite.GetScale().x,
                            m_sprite.GetPosition().y - m_sprite.GetOrigin().y * m_sprite.GetScale().y);
    return sf::FloatRect(leftCorner, m_sprite.GetSize());
}

void Ship::update(const sf::Input &Input, const sf::Vector2f &mousePos, float elapsedTime, std::list<Shot *> &shotList)
{
    if(mousePos.x > 192 and mousePos.x < 832)
    m_sprite.SetPosition(mousePos);
    m_timer += elapsedTime;
    if(Input.IsMouseButtonDown(sf::Mouse::Left) and m_timer > 0.1f){
        shotList.push_back(new NormalShot(shotImage, m_sprite.GetPosition()-sf::Vector2f(0, m_sprite.GetSize().y/2),
                                          sf::Vector2f(sf::Randomizer::Random(-10, 10), -400)));
        m_timer -= 0.1f;
    }
    if(m_timer > 0.1f)
        m_timer = 0.1f;
}

void Ship::draw(sf::RenderTarget& target) const
{
    target.Draw(m_sprite);
}
