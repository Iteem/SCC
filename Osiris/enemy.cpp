#include "enemy.hpp"
#include "normalshot.hpp"

#include "imagemanager.hpp"

Enemy::Enemy()
{
    sf::Image *tmp = IM.get("data/enemy.png");
    m_sprite.SetImage(*tmp);
    m_sprite.SetOrigin(tmp->GetWidth()/2, tmp->GetHeight()/2);
    m_sprite.Resize(0, 80);
    m_sprite.SetScaleX(m_sprite.GetScale().y);

    m_sprite.SetPosition(sf::Randomizer::Random(192, 832), sf::Randomizer::Random(50, 200));

    m_timer = 0;
}

Enemy::~Enemy()
{
}

sf::FloatRect Enemy::GetRect(void) const
{
    sf::Vector2f leftCorner(m_sprite.GetPosition().x - m_sprite.GetOrigin().x * m_sprite.GetScale().x,
                            m_sprite.GetPosition().y - m_sprite.GetOrigin().y * m_sprite.GetScale().y);
    return sf::FloatRect(leftCorner, m_sprite.GetSize());
}

void Enemy::update(float elapsedTime, std::list<Shot *> &shotList)
{
    m_timer += elapsedTime;
    if(m_timer > 0.5f){
        shotList.push_back(new NormalShot((IM.get("data/enemyShot.png")), m_sprite.GetPosition()+sf::Vector2f(0, m_sprite.GetSize().y/2),
                                          sf::Vector2f(sf::Randomizer::Random(-100, 100), 400)));
        m_timer -= 0.5f;
    }
}

void Enemy::draw(sf::RenderTarget& target) const
{
    target.Draw(m_sprite);
}
