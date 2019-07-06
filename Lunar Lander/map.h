#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

class Map
{
    public:
        Map(sf::RenderWindow&, std::string Map, int Width, int Height, int TWidth, int THeight);
        ~Map(){};
        void Update(sf::Vector2f);
        void DrawBackground(void);
        void DrawMap(void);
        bool IsOnPlatform(int i, int j);
        bool IsPixel(int i, int j);
        char GetTile(int x, int y);
        void SetMap(std::string Map, int Width, int Height, int TWidth, int THeight){};
    private:
        int MapWidth;
        int MapHeight;
        int TileWidth;
        int TileHeight;
        sf::RenderWindow &App;
        sf::Image TerrainImage, PlatformImage, BackgroundImage;
        sf::Image GoalPlatformImage, StartPlatformImage;
        sf::Sprite BackgroundSprite;
        std::list<sf::Sprite> TerrainToDraw;
        std::string CharMap;
        sf::Vector2f Pos;
        void ReloadMap(void);
};

#endif // MAP_H_INCLUDED
