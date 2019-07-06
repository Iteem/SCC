#include "player.hpp"

#include "imagemanager.hpp"

const float Speed = 150;

Player::Player(void) :
m_bombTimer(0)
{
}

Player::~Player()
{
}

bool Player::init(sf::Vector2f startPos, const std::string &path)
{
    m_sprite.SetImage(*IM.get(path));
    m_sprite.Resize(16, 16);
    m_sprite.SetPosition(startPos);

    m_leftKey = sf::Key::Left;
    m_rightKey = sf::Key::Right;
    m_downKey = sf::Key::Down;
    m_upKey = sf::Key::Up;
    m_dropBombKey = sf::Key::Return;

    return true;
}

bool Player::update(float elapsedTime, const sf::Input &input, const Map &map, std::list< Bomb > &bomb_list, const std::list<Explosion> &explosion_list)
{
    m_bombTimer += elapsedTime;

    if(input.IsKeyDown(m_downKey)){
        m_sprite.Move(0, Speed*elapsedTime);
        if(collide(map))
            m_sprite.Move(0, -Speed*elapsedTime);
    }
    if(input.IsKeyDown(m_upKey)){
        m_sprite.Move(0, -Speed*elapsedTime);
        if(collide(map))
            m_sprite.Move(0, Speed*elapsedTime);
    }
    if(input.IsKeyDown(m_leftKey)){
        m_sprite.Move(-Speed*elapsedTime, 0);
        if(collide(map))
            m_sprite.Move(Speed*elapsedTime, 0);
    }
    if(input.IsKeyDown(m_rightKey)){
        m_sprite.Move(Speed*elapsedTime, 0);
        if(collide(map))
            m_sprite.Move(-Speed*elapsedTime, 0);
    }

    if(input.IsKeyDown(m_dropBombKey) and m_bombTimer > 0.2f){
        bomb_list.push_back(Bomb(sf::Vector2i(static_cast<int>(m_sprite.GetPosition().x + 8)/32,
                                              static_cast<int>(m_sprite.GetPosition().y + 8)/32)));
        m_bombTimer = 0.f;
    }

    sf::Vector2i lu(m_sprite.GetPosition().x/32, m_sprite.GetPosition().y/32);
    sf::Vector2i lb(m_sprite.GetPosition().x/32, (m_sprite.GetPosition().y+m_sprite.GetSize().y)/32);
    sf::Vector2i ru((m_sprite.GetPosition().x+m_sprite.GetSize().x)/32, (m_sprite.GetPosition().y+m_sprite.GetSize().y)/32);
    sf::Vector2i rb((m_sprite.GetPosition().x+m_sprite.GetSize().x)/32, m_sprite.GetPosition().y/32);

    for(std::list<Explosion>::const_iterator it = explosion_list.begin(); it != explosion_list.end(); ++it){
        if(lu == it->getPosition() or lb == it->getPosition() or ru == it->getPosition() or rb == it->getPosition())
            return true;
    }
    return false;
}

void Player::setUpKey(sf::Key::Code key)
{
    m_upKey = key;
}

void Player::setDownKey(sf::Key::Code key)
{
    m_downKey = key;
}

void Player::setRightKey(sf::Key::Code key)
{
    m_rightKey = key;
}

void Player::setLeftKey(sf::Key::Code key)
{
    m_leftKey = key;
}

void Player::setDropBombKey(sf::Key::Code key)
{
    m_dropBombKey = key;
}


bool Player::collide(const Map &map)
{
    sf::Vector2i lu(m_sprite.GetPosition().x/32, m_sprite.GetPosition().y/32);
    sf::Vector2i lb(m_sprite.GetPosition().x/32, (m_sprite.GetPosition().y+m_sprite.GetSize().y)/32);
    sf::Vector2i ru((m_sprite.GetPosition().x+m_sprite.GetSize().x)/32, (m_sprite.GetPosition().y+m_sprite.GetSize().y)/32);
    sf::Vector2i rb((m_sprite.GetPosition().x+m_sprite.GetSize().x)/32, m_sprite.GetPosition().y/32);

    return map.getTile(lu)!='.' or map.getTile(lb)!='.' or map.getTile(ru)!='.' or map.getTile(rb)!='.';
}

void Player::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_sprite);
}
