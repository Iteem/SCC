#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "resourcemanager.hpp"
#include <SFML/Graphics/Texture.hpp>

class TextureManager : public ResourceManager<sf::Texture>
{
    public:
        TextureManager();
        virtual ~TextureManager();
    private:
        virtual sf::Texture *load(const std::string &path);
};

extern TextureManager texManager;

#endif // TEXTUREMANAGER_HPP
