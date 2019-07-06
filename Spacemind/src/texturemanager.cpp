#include "texturemanager.hpp"

TextureManager texManager;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

sf::Texture *TextureManager::load(const std::string &path)
{
    sf::Texture *tmp = new sf::Texture;
    if(!tmp->LoadFromFile(path))
    {
        delete tmp;
        tmp = NULL;
    }
    return tmp;
}
