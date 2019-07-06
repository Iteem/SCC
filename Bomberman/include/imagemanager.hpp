#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include "resourcemanager.hpp"
#include <SFML/Graphics/Image.hpp>

class ImageManager : public ResourceManager<sf::Image>
{
    public:
        ImageManager();
        virtual ~ImageManager();
    private:
        virtual sf::Image *load(const std::string &path);
};

extern ImageManager IM;

#endif // IMAGEMANAGER_HPP
