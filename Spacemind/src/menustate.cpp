#include "menuState.hpp"

#include <SFML/Graphics.hpp>

#include "texturemanager.hpp"
#include "fontmanager.hpp"

MenuState::MenuState(Shared &shared) :
State(shared),
m_exitButton(0)
{
}

MenuState::~MenuState()
{
}

bool MenuState::init(void)
{
	if(!m_shared.audioManager.isLoaded()){
		m_shared.audioManager.loadListFromFile(m_shared.config.getStringValue("musiclist"));
	}
	if(m_shared.config.getStringValue("playmusic") == "true"){
		m_shared.audioManager.play();
	}

	sf::Vector2f windowSize = app.GetDefaultView().GetSize();

	sf::Texture *tex;
	tex = texManager.get(m_shared.config.getStringValue("menubackground"));
	if(tex == 0){
		std::cerr << "Error Menubackground not found." << std::endl;
		return false;
	}
	m_background.SetTexture(*tex);

	//scale image(the width fits the screen width after)
	float scale = windowSize.x / tex->GetWidth();
	m_background.SetScale(scale, scale);

	//centre the image on the y-axis or scale it again so the screen gets filled
	float y_translation = (windowSize.y - tex->GetHeight()*scale)/2.f;
	if(y_translation > 0){
		scale = windowSize.y / tex->GetHeight
		();
		m_background.SetScale(scale, scale);
	} else {
		m_background.SetY(y_translation);
	}

	sf::Font *font;
	font = fontManager.get(m_shared.config.getStringValue("menufont"));
	if(font == 0){
		std::cerr << "Error: Font not found." << std::endl;
		return false;
	}
	//title
	m_title.SetFont(*font);
	m_title.SetString("Spacemind");
	m_title.SetCharacterSize(windowSize.y/10.f);
	m_title.SetOrigin(m_title.GetRect().Width/2.f, m_title.GetRect().Height/2.f);
	m_title.SetPosition(windowSize.x/2.f, windowSize.y/5.f);
	m_title.SetColor(sf::Color::Black);

	//buttons
	sf::Texture *texNormal  = texManager.get(m_shared.config.getStringValue("buttonimage"));
	sf::Texture *texHover   = texManager.get(m_shared.config.getStringValue("buttonimagehover"));
	sf::Texture *texPressed = texManager.get(m_shared.config.getStringValue("buttonimagepressed"));

	if(texNormal == 0 || texHover == 0 || texPressed == 0){
		std::cerr << "Error: Could not find all images for buttons." << std::endl;
		return false;
	}

	sf::FloatRect rect(0, -windowSize.y/100.f, windowSize.y/3.f, windowSize.y/15.f);

	sf::Text startText("Starten", *font, windowSize.y/20.f);
	m_startButton = new Button(startText, rect, texNormal, texHover, texPressed);
	m_startButton->SetOrigin(rect.Width/2.f, rect.Height/2.f);
	m_startButton->SetPosition(windowSize.x/2.f, 3*windowSize.y/7.f);
	m_startButtonPressed = false;

	sf::Text optionsText("Optionen", *font, windowSize.y/20.f);
	m_optionsButton = new Button(optionsText, rect, texNormal, texHover, texPressed);
	m_optionsButton->SetOrigin(rect.Width/2.f, rect.Height/2.f);
	m_optionsButton->SetPosition(windowSize.x/2.f, 4*windowSize.y/7.f);
	m_optionsButtonPressed = false;

	sf::Text exitText("Beenden", *font, windowSize.y/20.f);
	m_exitButton = new Button(exitText, rect, texNormal, texHover, texPressed);
	m_exitButton->SetOrigin(rect.Width/2.f, rect.Height/2.f);
	m_exitButton->SetPosition(windowSize.x/2.f, 5*windowSize.y/7.f);
	m_exitButtonPressed = false;

	return true;
}

void MenuState::destroy(void)
{
	delete m_startButton;
	delete m_optionsButton;
	delete m_exitButton;
}

State::Next MenuState::update(void)
{
	sf::Vector2f mousePos = app.ConvertCoords(sf::Mouse::GetPosition(app).x, sf::Mouse::GetPosition(app).y);
	sf::Event event;
	while (app.PollEvent(event)){
		if(event.Type == sf::Event::Closed)
			return State::Quit;

		m_startButton->handleEvent(event, mousePos);
		m_optionsButton->handleEvent(event, mousePos);
		m_exitButton->handleEvent(event, mousePos);
	}

	if(m_startButtonPressed && !m_startButton->isPressed()){ //button was clicked
		return State::Game;
	}
	m_startButtonPressed = m_startButton->isPressed();

	if(m_optionsButtonPressed && !m_optionsButton->isPressed()){ //button was clicked
		//does nothing yet
	}
	m_optionsButtonPressed = m_optionsButton->isPressed();

	if(m_exitButtonPressed && !m_exitButton->isPressed()){ //button was clicked
		return State::Quit;
	}
	m_exitButtonPressed = m_exitButton->isPressed();

	return State::NoChange;
}

void MenuState::draw(void) const
{
	app.Draw(m_background);
	app.Draw(m_title);

	app.Draw(*m_startButton);
	app.Draw(*m_exitButton);
	app.Draw(*m_optionsButton);
}
