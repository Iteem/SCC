#include "map.hpp"

#include "imagemanager.hpp"

#include <fstream>
#include <iostream>

Map::Map(void)
{
}

Map::~Map()
{
}

bool Map::loadFromFile(const std::string &path)
{
    std::ifstream file(path.c_str());
    if(!file.good()){
        std::cerr << "Failed to open file \"" << path << "\".";
        return false;
    }

    //delete old map
    m_charTiles.clear();
    m_tiles.clear();

    if(file.good())
        file >> m_size.x;
    else
        return false;
    if(file.good())
        file >> m_size.y;
    else
        return false;

    m_charTiles.resize(m_size.x);
    m_tiles.resize(m_size.x);
    for(size_t i = 0; i < m_size.x; ++i){
        m_charTiles[i].resize(m_size.y, '.');
        m_tiles[i].resize(m_size.y);
    }

    std::string str;
    std::getline(file, str);
    unsigned int linenum = 0;

    while(file.good()){
        std::getline(file, str);
        if(linenum < m_size.y){
            for(size_t i = 0; i < m_size.x and i < str.size(); ++i){
                setTile(sf::Vector2i(i,linenum), str[i]);
            }
        }
        linenum++;
    }


    return true;
}

char Map::getTile(sf::Vector2i pos) const
{
    if(pos.x >= 0 and pos.x < m_charTiles.size() and pos.y >= 0 and pos.y < m_charTiles[pos.x].size()){
        return m_charTiles[pos.x][pos.y];
    }
    return '-';
}

void Map::setTile(sf::Vector2i pos, char value)
{
    if(pos.x >= 0 and pos.x < m_charTiles.size() and pos.y >= 0 and pos.y < m_charTiles[pos.x].size()){
        m_charTiles[pos.x][pos.y] = value;
        sf::Sprite tmp;
        switch(m_charTiles[pos.x][pos.y]){
            case '-':
                tmp.SetImage(*IM.get("data/wall.png"));
                break;
            case '.':
                tmp.SetImage(*IM.get("data/floor.png"));
                break;
            case 'o':
                tmp.SetImage(*IM.get("data/chest.png"));
                break;
            default:
                tmp.SetImage(*IM.get("data/wall.png"));
        }
        tmp.Resize(32, 32);
        tmp.SetPosition(32*pos.x, 32*pos.y);
        m_tiles[pos.x][pos.y] = tmp;
    }
}

void Map::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    for(size_t i = 0; i < m_size.x; ++i){
        for(size_t j = 0; j < m_size.y; ++j){
            target.Draw(m_tiles[i][j]);
        }
    }
}
