#include <SFML/Graphics.hpp>
#include <fstream>
#include <list>
#include <string>

#include "menu.h"
#include "button.h"

class LevelButton : public Button
{
    public:
        LevelButton(sf::RenderWindow &Window, float PositionY, std::string Label) : Button(Window, PositionY, Label, 15){};
        ~LevelButton(){};
        std::string DirName;
};

struct Level
{
    std::string Name;
    std::string DirName;
};

enum Side
{
    MainSide,
    PlaySide,
    HighscoreSide,
    TutorialSide
};

bool RunMenu(sf::RenderWindow &App, sf::Font &Font, std::string &lvl)
{
    App.SetView(App.GetDefaultView());

    Side CurSide = MainSide;

    std::ifstream File("data/levels/levels.cll", std::ios::in);
    if(!File.good())
        return false;

    std::list<Level> Levels;

    while(!File.eof())
    {
        Level tmp;
        getline(File, tmp.Name);
        if(!File.eof())
        {
            getline(File, tmp.DirName);
            Levels.push_back(tmp);
        }
    }

    Button::SetFont(&Font);

    std::list<Level>::iterator it = Levels.begin();
    std::list<Level>::iterator CurPos = Levels.begin();

    LevelButton LvlButton1(App, 200, it->Name);
    LvlButton1.DirName = it->DirName + ".clm";
    LevelButton LvlButton2(App, 250, "");
    LevelButton LvlButton3(App, 300, "");
    LevelButton LvlButton4(App, 350, "");
    ++it;
    if(it!=Levels.end())
    {
        LvlButton2.SetText(it->Name);
        LvlButton2.DirName = it->DirName + ".clm";
        ++it;
    }
    if(it!=Levels.end())
    {
        LvlButton3.SetText(it->Name);
        LvlButton3.DirName = it->DirName + ".clm";
        ++it;
    }
    if(it!=Levels.end())
    {
        LvlButton4.SetText(it->Name);
        LvlButton4.DirName = it->DirName + ".clm";
    }
    Button Back(App, 400, "Zurück");

    Button Play(App, 200, "Start");
    Button Highscore(App, 275, "Highscore");
    Button Tutorial(App, 350, "Tutorial");
    Button Exit(App, 425, "Ende");

    sf::Image TutorialImage;
    if(!TutorialImage.LoadFromFile("data/tutorial.png"))
        return false;
    sf::Sprite TutorialSprite(TutorialImage);
    Button BackFromTut(App, sf::Vector2f(500, 550), "Zurück", 30, sf::Color::White);


    sf::Event Event;

    sf::Image BackgroundImage;
    if(!BackgroundImage.LoadFromFile("data/background-menu.jpg"))
        return false;
    sf::Sprite Background(BackgroundImage);

    while(true)
    {
        while(App.GetEvent(Event))
        {
            if(Event.Type == sf::Event::Closed)
                return false;
        }

        switch(CurSide)
        {
            case MainSide:
                if(Play.Update())
                    CurSide = PlaySide;
                Highscore.Update();
                if(Tutorial.Update())
                    CurSide = TutorialSide;
                if(Exit.Update())
                    return false;
                break;
            case PlaySide:
                if(LvlButton1.Update())
                {
                    lvl = LvlButton1.DirName;
                    return true;
                }
                if(LvlButton2.Update())
                {
                    lvl = LvlButton2.DirName;
                    return true;
                }
                if(LvlButton3.Update())
                {
                    lvl = LvlButton3.DirName;
                    return true;
                }
                if(LvlButton4.Update())
                {
                    lvl = LvlButton4.DirName;
                    return true;
                }
                if(Back.Update())
                    CurSide = MainSide;
                break;
            case HighscoreSide:
                break;
            case TutorialSide:
                if(BackFromTut.Update())
                    CurSide = MainSide;
                break;
        }

        App.Clear();

        App.Draw(Background);

        switch(CurSide)
        {
            case MainSide:
                Play.Draw();
                Highscore.Draw();
                Tutorial.Draw();
                Exit.Draw();
                break;
            case PlaySide:
                LvlButton1.Draw();
                LvlButton2.Draw();
                LvlButton3.Draw();
                LvlButton4.Draw();
                Back.Draw();
                break;
            case HighscoreSide:
                break;
            case TutorialSide:
                App.Draw(TutorialSprite);
                BackFromTut.Draw();
                break;
        }

        App.Display();
    }
}
