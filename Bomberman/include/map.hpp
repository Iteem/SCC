#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Map : public sf::Drawable
{
    public:
        Map(void);
        ~Map();

        bool loadFromFile(const std::string &path);

        char getTile(sf::Vector2i pos) const;
        void setTile(sf::Vector2i pos, char value);

    private:
        std::vector< std::vector<char> > m_charTiles;
        std::vector< std::vector<sf::Sprite> > m_tiles;

        sf::Vector2<size_t> m_size;

        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
};

#endif // MAP_HPP_INCLUDED
