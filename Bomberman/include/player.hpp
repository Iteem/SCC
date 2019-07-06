#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>
#include <string>

#include "map.hpp"
#include "bomb.hpp"
#include "explosion.hpp"

class Player : public sf::Drawable
{
    public:
        Player(void);
        ~Player();

        bool init(sf::Vector2f startPos, const std::string &path);

        void setUpKey(sf::Key::Code key);
        void setDownKey(sf::Key::Code key);
        void setRightKey(sf::Key::Code key);
        void setLeftKey(sf::Key::Code key);
        void setDropBombKey(sf::Key::Code key);

        bool update(float elapsedTime, const sf::Input &input, const Map &map, std::list< Bomb > &bomb_list, const std::list<Explosion> &explosion_list);

    private:
        sf::Sprite m_sprite;
        float m_bombTimer;

        sf::Key::Code m_upKey;
        sf::Key::Code m_downKey;
        sf::Key::Code m_rightKey;
        sf::Key::Code m_leftKey;
        sf::Key::Code m_dropBombKey;

        bool collide(const Map &map);
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
};

#endif // PLAYER_HPP_INCLUDED
