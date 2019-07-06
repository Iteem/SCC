#include "game.hpp"
#include "shared.hpp"
#include "state.hpp"

#include "introstate.hpp"
#include "menustate.hpp"
#include "gamestate.hpp"

Game::Game(int argc, char **argv)
{
}

Game::~Game()
{
}

int Game::run(void)
{
    //set up a window
    sf::ContextSettings settings;
    settings.AntialiasingLevel = 2;
    sf::VideoMode videoMode(1024, 768, 32);

    sf::RenderWindow app(videoMode, "Osiris", sf::Style::Default, settings);//sf::Style::Fullscreen, settings);
    //app.UseVerticalSync(true);
    app.SetFramerateLimit(60);

    //set up a state
    Shared shared(app, videoMode);
    State *state;
    state = new MenuState(shared);//IntroState(shared);
    state->init();

    while(true){
        State::Next next = state->update();
        if(next != State::NoChange){ //the state will change
            //destroy the old one
            state->destroy();
            delete state;

            //create and initialize an new state
            switch(next){
                case State::Intro:
                    state = new IntroState(shared);
                    break;
                case State::Menu:
                    state = new MenuState(shared);
                    break;
                case State::Game:
                    state = new GameState(shared);
                    break;
                default:
                    return 0; //State::Quit or unknown statetyp, exit
            }
            state->init();
        }

        state->draw();

        app.Display();
    }
}
