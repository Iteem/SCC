#include "introState.hpp"

IntroState::IntroState(Shared &shared) :
State(shared)
{
}
IntroState::~IntroState()
{
}

bool IntroState::init(void)
{
	time = 0;

	if(!texLogo.LoadFromFile("data/SFMLLogo_Text-Icons.png") || !texWheel.LoadFromFile("data/SFMLLogo_Wheel.png")){
		return false;
	}


	sf::Vector2i windowSize = static_cast<sf::Vector2i>(app.GetDefaultView().GetSize());

	logo.SetTexture(texLogo);
	logo.SetOrigin(texLogo.GetWidth()/2, texLogo.GetHeight()/2);
	logo.SetPosition(static_cast<sf::Vector2f>(windowSize/2));

	wheel.SetTexture(texWheel);
	wheel.SetOrigin(texWheel.GetWidth()/2, texWheel.GetHeight()/2);
	wheel.SetPosition(static_cast<sf::Vector2f>(windowSize/2));

	return true;
}

void IntroState::destroy(void)
{
}

State::Next IntroState::update(void)
{
	sf::Event event;
	while (app.PollEvent(event)){
		if(event.Type == sf::Event::Closed)
			return State::Quit;
		if(event.Type == sf::Event::KeyPressed)
			return State::Menu;
	}

	time += app.GetFrameTime();

	wheel.SetRotation(time/50.f);
	if(time > 3000){
		int col = 255 - (time-3000)/4;
		if(col < 0)
			col = 0;
		logo.SetColor(sf::Color(col, col, col));
		wheel.SetColor(sf::Color(col, col, col));
	}

	if(time > 4000)
		return State::Menu;
	return State::NoChange;
}

void IntroState::draw(void) const
{
	app.Draw(wheel);
	app.Draw(logo);
}
