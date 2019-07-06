#include "imagemanager.hpp"

ImageManager IM;

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

sf::Image *ImageManager::load(const std::string &path)
{
    sf::Image *tmp = new sf::Image;
    if(!tmp->LoadFromFile(path))
    {
        delete tmp;
        tmp = NULL;
    }
    return tmp;
}
