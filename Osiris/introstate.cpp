#include "introState.hpp"
#include <cmath>

IntroState::IntroState(Shared &shared) :
State(shared),
cursor(sf::Color::Black, 15, 0.1f)
{
}
IntroState::~IntroState()
{
}

void IntroState::init(void)
{
    time = 0;

    im.LoadFromFile("data/patrick-tux.png");

    ts.SetImage(im);
    ts.AddPoint(  0,   0, 0, 0);
    ts.AddPoint(  0, 200, 0, 1);
    ts.AddPoint(200, 200, 1, 1);
    ts.AddPoint(200,   0, 1, 0);
    ts.SetOrigin(100, 100);
    ts.SetPosition(1024/2, 768/2);
    ts.SetRotation(270);

    app.ShowMouseCursor(false);

    papyrus.LoadFromFile("data/papyrus.ttf");

    text1.SetFont(papyrus);
    text1.SetColor(sf::Color::Black);
    text1.SetPosition(1024/2, 600);
    text1.SetCharacterSize(20);
    text1.SetString("Createt by Iteem");
    text1.SetOrigin(text1.GetRect().Width/2.f, text1.GetRect().Height/2.f);

    text2.SetFont(papyrus);
    text2.SetColor(sf::Color::Black);
    text2.SetPosition(1024/2, 650);
    text2.SetCharacterSize(20);
    text2.SetString("Music by Galdson");
    text2.SetOrigin(text2.GetRect().Width/2.f, text2.GetRect().Height/2.f);
}

void IntroState::destroy(void)
{
    app.ShowMouseCursor(true);
}

void IntroState::pause(void)
{
}

void IntroState::resume(void)
{
}

State::Next IntroState::update(void)
{
    sf::Event event;
    while(app.GetEvent(event))
    {
        if(event.Type == sf::Event::Closed){
            return State::Quit;
        }
        if(event.Type == sf::Event::KeyPressed){
            //if(event.Key.Code == sf::Key::Escape){
            //    return State::Quit;
            //}else{
                return State::Menu;
            //}
        }
    }

    cursor.SetPosition(app.ConvertCoords(app.GetInput().GetMouseX(), app.GetInput().GetMouseY()));
    cursor.update(app.GetFrameTime());

    time += app.GetFrameTime();

    ts.SetPointTexturePosition(0, sf::Vector2f(-0.25f + 0.25f*std::cos(time*3.14), 0));
    ts.SetPointTexturePosition(1, sf::Vector2f( 1.25f - 0.25f*std::cos(time*3.14), 0));
    ts.SetPointTexturePosition(3, sf::Vector2f(-0.25f + 0.25f*std::sin(time*3.14), 1));
    ts.SetPointTexturePosition(2, sf::Vector2f( 1.25f - 0.25f*std::sin(time*3.14), 1));

    //ts.Rotate(app.GetFrameTime()*180);
    //ts.SetX(400 + std::cos(time*3.14)*200);


    return State::NoChange;
}

void IntroState::draw(void) const
{
    app.Clear(sf::Color::White);

    app.Draw(ts);

    app.Draw(text1);
    app.Draw(text2);

    app.Draw(cursor);
}
