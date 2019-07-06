#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "game.h"
#include "menu.h"

int main(void)
{
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Crazy Lander");
    App.UseVerticalSync(true);
    sf::Font Font;
    if(!Font.LoadFromFile("data/ethnocen.ttf", 25))
        return EXIT_FAILURE;
    std::string lvl;

    sf::Music Zone;
    if(!Zone.OpenFromFile("data/zone.ogg"))
        return EXIT_FAILURE;
    Zone.SetLoop(true);
    Zone.SetVolume(75.f);
    Zone.Play();

    while(RunMenu(App, Font, lvl))
    {
        if(!RunGame(App, Font, lvl))
            break;
    }

    return EXIT_SUCCESS;
}
