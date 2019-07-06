#include "fontmanager.hpp"

FontManager fontManager;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

sf::Font *FontManager::load(const std::string &path)
{
    sf::Font *tmp = new sf::Font;
    if(!tmp->LoadFromFile(path))
    {
        delete tmp;
        tmp = NULL;
    }
    return tmp;
}
