#include <SFML/Graphics.hpp>

#include "Map.h"

Map::Map(sf::RenderWindow& Window, std::string Map, int Width, int Height, int TWidth, int THeight) : App(Window)
{
    TerrainImage.LoadFromFile("data/terrain-texture.png");
    PlatformImage.LoadFromFile("data/platform.png");
    StartPlatformImage.LoadFromFile("data/platform-start.png");
    GoalPlatformImage.LoadFromFile("data/platform-goal.png");

    CharMap = Map;

    MapWidth = Width;
    MapHeight = Height;
    TileWidth = TWidth;
    TileHeight = THeight;

    Pos = sf::Vector2f(0,0);

    ReloadMap();

    sf::Image HelpImage;
    if(HelpImage.LoadFromFile("data/background.png"))
    BackgroundImage.Create(900, 700, sf::Color::White);
    for(int i = 0; i < static_cast<int>(BackgroundImage.GetWidth()); i += HelpImage.GetWidth())
    {
        for(int j = 0; j < static_cast<int>(BackgroundImage.GetHeight()); j += HelpImage.GetHeight())
        {
            BackgroundImage.Copy(HelpImage, i, j);
        }
    }
    BackgroundSprite.SetImage(BackgroundImage);
    BackgroundSprite.SetCenter(450, 350);
}

void Map::Update(sf::Vector2f Position)
{
    if(static_cast<int>(Position.x/TileWidth) != static_cast<int>(Pos.x/TileWidth) or static_cast<int>(Position.y/TileHeight) != static_cast<int>(Pos.y/TileHeight))
    {
        Pos = Position;
        ReloadMap();
    }
    sf::Vector2f h(static_cast<int>(Position.x) - static_cast<int>(Position.x) % 16, static_cast<int>(Position.y) - static_cast<int>(Position.y) % 16);
    BackgroundSprite.SetPosition(h);
    Pos = Position;
}

void Map::DrawBackground(void)
{
    App.Draw(BackgroundSprite);
}

void Map::DrawMap(void)
{
    for(std::list<sf::Sprite>::iterator i = TerrainToDraw.begin(); i != TerrainToDraw.end(); ++i)
        App.Draw(*i);
}

bool Map::IsOnPlatform(int i, int j)
{
    char h = CharMap[static_cast<int>(i/TileWidth) + static_cast<int>((j/TileHeight)*MapWidth)];
    if(h == 'P' or h == 'S' or h == 'Z')
        return true;
    return false;
}

bool Map::IsPixel(int i, int j)
{
    if(CharMap[static_cast<int>(i/TileWidth) + static_cast<int>(j/TileHeight*MapWidth)] != ' ')
        return true;
    return false;
}

void Map::ReloadMap()
{
    TerrainToDraw.clear();
    sf::Vector2i h(static_cast<int>((Pos.x-400)/TileWidth-2), static_cast<int>((Pos.y-300)/TileHeight-2));
    sf::Vector2i h2(static_cast<int>((Pos.x+400)/TileWidth+2), static_cast<int>((Pos.y+300)/TileHeight+2));
    sf::Sprite tmp;
    for(int i = h.x; i < h2.x; ++i)
    {
        for(int j = h.y; j < h2.y; ++j)
        {
            if(i >= 0 and i < MapWidth and j >=0 and j < MapHeight)
            {
                switch(CharMap[i+j*MapWidth])
                {
                    case 'X':
                        tmp.SetImage(TerrainImage);
                        tmp.SetPosition(i*TileWidth, j*TileHeight);
                        TerrainToDraw.push_back(tmp);
                        break;
                    case 'P':
                        tmp.SetImage(PlatformImage);
                        tmp.SetPosition(i*TileWidth, j*TileHeight);
                        TerrainToDraw.push_back(tmp);
                        break;
                    case 'S':
                        tmp.SetImage(StartPlatformImage);
                        tmp.SetPosition(i*TileWidth, j*TileHeight);
                        TerrainToDraw.push_back(tmp);
                        break;
                    case 'Z':
                        tmp.SetImage(GoalPlatformImage);
                        tmp.SetPosition(i*TileWidth, j*TileHeight);
                        TerrainToDraw.push_back(tmp);
                        break;
                }
            }
            else
            {
                sf::Sprite tmp(TerrainImage);
                tmp.SetPosition(i*TileWidth, j*TileHeight);
                TerrainToDraw.push_back(tmp);
            }
        }
    }
}

char Map::GetTile(int x, int y)
{
    if(x >= 0 and x < MapWidth and y >= 0 and y < MapHeight)
        return CharMap[x+y*MapWidth];
    return 'X';
}
