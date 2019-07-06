#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

class Map
{
    public:
        Map();
        ~Map();

        bool load( std::string path );
        void update(sf::Vector2f);

        void draw( sf::RenderTarget &target ) const;

        bool isOnPlatform(unsigned int i, unsigned int j);
        bool isPixel(unsigned int i, unsigned int j);
        int getTile(unsigned int x, unsigned int y);

        sf::Vector2u getStartPos();
        sf::Vector2u getDimension();
        sf::Vector2u getTileDimension();
    private:
        sf::Vector2u m_dimension;
		sf::Vector2u m_tileDimension;
        sf::Vector2u m_startPos;

        sf::Texture m_texture;
        std::vector<int> m_tiles;

        mutable std::list<sf::Sprite> TerrainToDraw;
        std::string CharMap;
        sf::Vector2f Pos;

        void compile() const;
};

#endif // MAP_H_INCLUDED
