#include "menuState.hpp"

#include "imagemanager.hpp"

const int SizeOfQuadrat = 75;//150;
const sf::Color QuadratColor(200, 200, 200);//(146, 210, 125);

MenuState::MenuState(Shared &shared) :
State(shared)
{
}

MenuState::~MenuState()
{
}

void MenuState::init(void)
{
    //make background
    sf::Image quadratImage;
    quadratImage.Create(SizeOfQuadrat, SizeOfQuadrat, QuadratColor);
    m_backgroundImage.Create(1200, 1200, sf::Color(255, 255, 255));
    for(unsigned int i=0; i<1200; i+=SizeOfQuadrat)
    {
        for(unsigned int j=0; j<1200; j+=SizeOfQuadrat * 2)
            m_backgroundImage.Copy(quadratImage, i, j);
        i+=SizeOfQuadrat;
        for(unsigned int j=SizeOfQuadrat; j<1200; j+=SizeOfQuadrat * 2)
            m_backgroundImage.Copy(quadratImage, i, j);
    }
    m_background.SetImage(m_backgroundImage);
    m_background.SetOrigin(600, 600);
    m_background.SetPosition(800 / 2, 600 / 2);

    m_logo.SetImage(*IM.get("data/logo.png"));
    m_logo.SetOrigin(m_logo.GetSize()/2.f);
    m_logo.SetPosition(400, 150);

    m_startText.SetString("Start");
    m_helpText.SetString("Hilfe");
    m_exitText.SetString("Beenden");

    m_startText.SetOrigin(0, m_startText.GetRect().Height / 2.f);
    m_helpText.SetOrigin(0, m_helpText.GetRect().Height / 2.f);
    m_exitText.SetOrigin(0, m_exitText.GetRect().Height / 2.f);

    m_startText.SetPosition(350, 300);
    m_helpText.SetPosition(350, 375);
    m_exitText.SetPosition(350, 450);

    m_startText.SetColor(sf::Color::Black);
    m_helpText.SetColor(sf::Color::Black);
    m_exitText.SetColor(sf::Color::Black);

    m_marker = sf::Shape::Rectangle(0, 0, 20, 20, sf::Color::Black);
    m_marker.SetOrigin(10, 10);
    m_marker.SetPosition(330, 300);

    m_selected = 0;
    m_displayHelp = false;

    m_howto.SetImage(*IM.get("data/howto.png"));
    m_howto.SetOrigin(m_howto.GetSize()/2.f);
    m_howto.SetPosition(400, 300);
}

void MenuState::destroy(void)
{
}

void MenuState::pause(void)
{
}

void MenuState::resume(void)
{
}

State::Next MenuState::update(void)
{
    sf::Event event;
    while(app.GetEvent(event)){
        if(event.Type == sf::Event::Closed){
            return State::Quit;
        }
        if(event.Type == sf::Event::KeyPressed){
            if(event.Key.Code == sf::Key::Escape){
                if(m_displayHelp)
                    m_displayHelp = false;
                else
                    return State::Quit;
            } else if(event.Key.Code == sf::Key::Down){
                m_selected++;
                if(m_selected > 2)
                    m_selected = 0;
            } else if(event.Key.Code == sf::Key::Up){
                m_selected--;
                if(m_selected < 0)
                    m_selected = 2;
            } else if(event.Key.Code == sf::Key::Return){
                if(!m_displayHelp){
                    switch(m_selected){
                        case 0:
                            return State::Game;
                            break;
                        case 1:
                            m_displayHelp = true;
                            break;
                        case 2:
                            return State::Quit;
                            break;
                    }
                }
            }
            m_marker.SetY(m_selected*75+300);
        }
    }

    float elapsedTime = app.GetFrameTime();
    const sf::Input &input = app.GetInput();
    sf::Vector2f mousePos(app.ConvertCoords(input.GetMouseX(), input.GetMouseY()));

    m_background.Rotate(10*elapsedTime);

    return State::NoChange;
}

void MenuState::draw(void) const
{
    app.Clear(sf::Color::White);

    app.Draw(m_background);
    app.Draw(m_logo);

    app.Draw(m_startText);
    app.Draw(m_exitText);
    app.Draw(m_helpText);

    app.Draw(m_marker);

    if(m_displayHelp)
        app.Draw(m_howto);
}
