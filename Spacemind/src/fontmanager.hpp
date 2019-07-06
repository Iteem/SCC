#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include "resourcemanager.hpp"
#include <SFML/Graphics/Font.hpp>

class FontManager : public ResourceManager<sf::Font>
{
    public:
        FontManager();
        virtual ~FontManager();
    private:
        virtual sf::Font *load(const std::string &path);
};

extern FontManager fontManager;

#endif // FONTMANAGER_HPP
