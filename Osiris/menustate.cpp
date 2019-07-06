#include "menuState.hpp"

MenuState::MenuState(Shared &shared) :
State(shared),
cursor(sf::Color::Black, 15, 0.1f)
{
}

MenuState::~MenuState()
{
}

void MenuState::init(void)
{
    app.ShowMouseCursor(false);

    backgroundImage.LoadFromFile("data/background_menu.jpg");
    background.SetImage(backgroundImage);

    font.LoadFromFile("data/papyrus.ttf");

    sf::Text tmpText("Start", font, 20);
    tmpText.SetColor(sf::Color::White);
    tmpText.SetStyle(sf::Text::Bold);
    sf::FloatRect rect(0, 0, 140, 40);

    startButton = new Button(tmpText, rect);
    startButton->SetOrigin(70, 25);
    startButton->SetPosition(512, 350);

    tmpText.SetString("Info");
    aboutButton = new Button(tmpText, rect);
    aboutButton->SetOrigin(70, 25);
    aboutButton->SetPosition(512, 425);

    tmpText.SetString("Beenden");
    exitButton = new Button(tmpText, rect);
    exitButton->SetOrigin(70, 25);
    exitButton->SetPosition(512, 500);

    startPressed = false;
    aboutPressed = false;
    exitPressed = false;

    music.OpenFromFile("data/album2/02 - Denilio.ogg");
    music.SetLoop(true);
    music.Play();
}

void MenuState::destroy(void)
{
    delete startButton;
    delete aboutButton;
    delete exitButton;

    app.ShowMouseCursor(true);
}

void MenuState::pause(void)
{
}

void MenuState::resume(void)
{
}

State::Next MenuState::update(void)
{
    const sf::Input &input = app.GetInput();
    sf::Vector2f mousePos(app.ConvertCoords(input.GetMouseX(), input.GetMouseY()));

    sf::Event event;
    while(app.GetEvent(event)){
        if(event.Type == sf::Event::Closed){
            return State::Quit;
        }
        /*if(event.Type == sf::Event::KeyPressed){
            if(event.Key.Code == sf::Key::Escape){
                return State::Quit;
            }
        }*/
        startButton->handleEvent(event, mousePos);
        aboutButton->handleEvent(event, mousePos);
        exitButton->handleEvent(event, mousePos);

    }

     if(startButton->isPressed())
         startPressed = true;
     else if(startPressed) //button not pressed, but once was pressed
         return State::Game;

     if(aboutButton->isPressed())
         aboutPressed = true;
     else if(aboutPressed)
         return State::Intro;

     if(exitButton->isPressed())
         exitPressed = true;
     else if(exitPressed)
         return State::Quit;


    cursor.SetPosition(mousePos);
    cursor.update(app.GetFrameTime());

    return State::NoChange;
}

void MenuState::draw(void) const
{
    app.Clear();

    app.Draw(background);

    app.Draw(*startButton);
    app.Draw(*aboutButton);
    app.Draw(*exitButton);

    app.Draw(cursor);
}
