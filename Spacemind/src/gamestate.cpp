#include "gameState.hpp"

#include <sstream>
#include <cmath>
#include <cstdlib>

#include "fontmanager.hpp"
#include "texturemanager.hpp"

GameState::GameState(Shared &shared) :
State(shared)
{
}

GameState::~GameState()
{
}

bool GameState::init(void)
{
	sf::Vector2f windowSize = app.GetDefaultView().GetSize();

	//background
	sf::Texture *tex;
	tex = texManager.get(m_shared.config.getStringValue("gamebackground"));
	if(tex == 0){
		std::cerr << "Error Gamebackground not found." << std::endl;
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

	//playing field
	tex = texManager.get(m_shared.config.getStringValue("fieldimage"));
	if(tex == 0) return false;
	m_field.SetTexture(*tex);
	m_field.SetDimension(sf::Vector2i(windowSize.x / 3.f, 4.f*windowSize.y/5.f));
	m_field.SetOrigin(static_cast<sf::Vector2f>(m_field.GetDimension())/2.f);
	m_field.SetPosition(windowSize/2.f);

	//lines
	size_t numberOfLines = 9;
	tex = texManager.get(m_shared.config.getStringValue("horizontallineimage"));
	if(tex == 0) return false;

	Spritebox tmpSB;
	tmpSB.SetTexture(*tex);
	tmpSB.SetDimension(sf::Vector2i(3.f*windowSize.x/15.f, 4.f));
	m_lines.resize(numberOfLines, tmpSB);
	//the first and last line need to be longer
	m_lines[0].SetDimension(sf::Vector2i(4.f*windowSize.x/15.f, 4.f));
	m_lines[m_lines.size()-1].SetDimension(sf::Vector2i(4.f*windowSize.x/15.f, 4.f));

	float stepSize = 4.f/5.f/(numberOfLines+1);

	for(unsigned int i = 0; i < numberOfLines; ++i){
		m_lines[i].SetPosition(11.f*windowSize.x/30.f, (1.f/10.f + (i+1)*stepSize) * windowSize.y);
	}


	m_lights.resize(numberOfLines-1);

	//holes
	tex = texManager.get(m_shared.config.getStringValue("holeimage"));
	if(tex == 0) return false;
	sf::Sprite tmpSprite(*tex);
	tmpSprite.SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
	tmpSprite.Resize(windowSize.y / 25.f, windowSize.y / 25.f);

	m_holes.resize(4);
	for(unsigned int i = 0; i < m_holes.size(); ++i){
		m_holes[i].resize(numberOfLines-1, tmpSprite);
		for(unsigned int j = 0; j < m_holes[i].size(); ++j){
			m_holes[i][j].SetPosition((11.5f+1.5f*i)*windowSize.x/30.f, (3.f/20.f + (j+1)*stepSize) * windowSize.y);
		}
	}

	//balls
	m_balls.resize(6);
	tmpSprite.SetTexture(*tex);
	tmpSprite.SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
	tmpSprite.Resize(windowSize.y / 25.f, windowSize.y / 25.f);
	for(unsigned int i = 0; i < m_balls.size(); ++i){
		std::stringstream stream;
		stream << (i+1);
		tex = texManager.get(m_shared.config.getStringValue("ballimage"+stream.str()));
		if(tex == 0) return false;
		tmpSprite.SetTexture(*tex, true);
		tmpSprite.SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
		tmpSprite.Resize(windowSize.y / 30.f, windowSize.y / 30.f);
		tmpSprite.SetPosition((11+i)*windowSize.x/30.f, 17.f/20.f * windowSize.y);
		m_balls[i] = tmpSprite;
	}

	//solution
	m_solution.resize(4);

	for(unsigned int i = 0; i < m_solution.size(); ++i){
		const sf::Texture *ctex = m_balls[rand()%6].GetTexture();
		tmpSprite.SetTexture(*ctex, true);
		tmpSprite.SetOrigin(ctex->GetWidth()/2.f, ctex->GetHeight()/2.f);
		tmpSprite.Resize(windowSize.y / 25.f, windowSize.y / 25.f);
		tmpSprite.SetPosition((11.5f+1.5f*i)*windowSize.x/30.f, 3.f/20.f * windowSize.y);
		m_solution[i] = tmpSprite;
	}

	m_curLine = 7;
	m_curColumn = 0;
	m_lineIsFilled = false;
	m_gameIsOver = false;;

	//buttons
	sf::Texture *texNormal  = texManager.get(m_shared.config.getStringValue("buttonimage"));
	sf::Texture *texHover   = texManager.get(m_shared.config.getStringValue("buttonimagehover"));
	sf::Texture *texPressed = texManager.get(m_shared.config.getStringValue("buttonimagepressed"));

	if(texNormal == 0 || texHover == 0 || texPressed == 0){
		std::cerr << "Error: Could not find all images for buttons." << std::endl;
		return false;
	}

	sf::Font *font = fontManager.get(m_shared.config.getStringValue("menufont"));
	if(font == 0) return false;

	sf::FloatRect rect(0, -windowSize.y/100.f, windowSize.y/3.f, windowSize.y/15.f);

	sf::Text OKText("OK", *font, windowSize.y/20.f);
	m_OKButton = new Button(OKText, rect, texNormal, texHover, texPressed);
	m_OKButton->SetPosition(3.f*windowSize.x/4.f, 3*windowSize.y/7.f);
	m_OKButtonPressed = false;

	sf::Text resetText(L"Löschen", *font, windowSize.y/20.f);
	m_resetButton = new Button(resetText, rect, texNormal, texHover, texPressed);
	m_resetButton->SetPosition(3.f*windowSize.x/4.f, 4*windowSize.y/7.f);
	m_resetButtonPressed = false;

	return true;
}

void GameState::destroy(void)
{
	delete m_OKButton;
	delete m_resetButton;
}

State::Next GameState::update(void)
{
	sf::Vector2f mousePos = app.ConvertCoords(sf::Mouse::GetPosition().x, sf::Mouse::GetPosition().y);
	sf::Event event;
	while (app.PollEvent(event)){
		if(event.Type == sf::Event::Closed)
			return State::Quit;
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Escape)
			return State::Menu;
		if(event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left){
			for(unsigned int i = 0; i < m_balls.size(); ++i){
				if(!m_lineIsFilled && !m_gameIsOver){
					sf::Vector2f vec = mousePos-m_balls[i].GetPosition();
					if(std::pow(vec.x, 2) + std::pow(vec.y, 2) < std::pow(m_balls[i].GetSize().x/2.f, 2)){
						const sf::Texture *tex = m_balls[i].GetTexture();
						sf::Vector2f size = m_holes[m_curColumn][m_curLine].GetSize();
						m_holes[m_curColumn][m_curLine].SetTexture(*tex, true);
						m_holes[m_curColumn][m_curLine].SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
						m_holes[m_curColumn][m_curLine].Resize(size);
						m_curColumn++;
						if(m_curColumn >= m_holes.size()){
							m_lineIsFilled = true;
						}
					}
				}
			}
		}
		m_OKButton->handleEvent(event, mousePos);
		m_resetButton->handleEvent(event, mousePos);
	}

	if(m_OKButtonPressed && !m_OKButton->isPressed() && m_lineIsFilled && !m_gameIsOver){ //button was clicked
		m_lineIsFilled = false;
		m_curColumn = 0;

		//check for fits
		bool barrays[4] = {false, false, false, false};
		bool barrayh[4] = {false, false, false, false};
		unsigned int pos = 0;
		sf::Vector2f windowSize = app.GetDefaultView().GetSize();
		size_t numberOfLines = 9;
		float stepSize = 4.f/5.f/(numberOfLines+1);
		unsigned int fullfits = 0;

		for(unsigned int i = 0; i < m_solution.size(); ++i){
			if(m_holes[i][m_curLine].GetTexture() == m_solution[i].GetTexture()){
				sf::Texture *tex = texManager.get(m_shared.config.getStringValue("lightgreen"));
				if(tex == 0) return State::Quit;
				sf::Sprite tmpSprite(*tex);
				tmpSprite.SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
				tmpSprite.Resize(windowSize.y / 50.f, windowSize.y / 50.f);
				tmpSprite.SetPosition((35.f+pos)*windowSize.x/60.f, (3.f/20.f + (m_curLine+1)*stepSize) * windowSize.y);
				m_lights[i].push_back(tmpSprite);
				fullfits++;

				barrays[i] = true;
				barrayh[i] = true;
				pos++;
			}
		}
		for(unsigned int i = 0; i < m_solution.size(); ++i){
			for(unsigned int j = 0; j < m_solution.size(); ++j){
				if(m_holes[j][m_curLine].GetTexture() == m_solution[i].GetTexture() && !(barrays[i]) && !(barrayh[j])){
					sf::Texture *tex = texManager.get(m_shared.config.getStringValue("lightyellow"));
					if(tex == 0) return State::Quit;
					sf::Sprite tmpSprite(*tex);
					tmpSprite.SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
					tmpSprite.Resize(windowSize.y / 50.f, windowSize.y / 50.f);
					tmpSprite.SetPosition((35.f+pos)*windowSize.x/60.f, (3.f/20.f + (m_curLine+1)*stepSize) * windowSize.y);
					m_lights[i].push_back(tmpSprite);

					barrays[i] = true;
					barrayh[j] = true;
					pos++;
				}
			}
		}

		if(m_curLine == 0 || fullfits == 4){
			m_gameIsOver = true;
		}
		m_curLine--;
	}
	if(m_resetButtonPressed && !m_resetButton->isPressed() && !m_gameIsOver){ //button was clicked
		m_lineIsFilled = false;
		m_curColumn = 0;

		const sf::Texture *tex = texManager.get(m_shared.config.getStringValue("holeimage"));
		if(tex == 0) return State::Quit;
		for(unsigned int i = 0; i < m_holes.size(); ++i){
			sf::Vector2f size = m_holes[m_curColumn][m_curLine].GetSize();
			m_holes[i][m_curLine].SetTexture(*tex, true);
			m_holes[i][m_curLine].SetOrigin(tex->GetWidth()/2.f, tex->GetHeight()/2.f);
			m_holes[i][m_curLine].Resize(size);
		}
	}
	m_OKButtonPressed = m_OKButton->isPressed();
	m_resetButtonPressed = m_resetButton->isPressed();

	return State::NoChange;
}

void GameState::draw(void) const
{
	app.Draw(m_background);

	app.Draw(m_field);
	for(unsigned int i = 0; i < m_lines.size(); ++i){
		app.Draw(m_lines[i]);
	}
	for(unsigned int i = 0; i < m_holes.size(); ++i){
		for(unsigned int j = 0; j < m_holes[i].size(); ++j){
			app.Draw(m_holes[i][j]);
		}
	}
	for(unsigned int i = 0; i < m_balls.size(); ++i){
		app.Draw(m_balls[i]);
	}
	if(m_gameIsOver){
		for(unsigned int i = 0; i < m_solution.size(); ++i){
			app.Draw(m_solution[i]);
		}
	}
	for(unsigned int i = 0; i < m_lights.size(); ++i){
		for(std::list<sf::Sprite>::const_iterator it = m_lights[i].begin(); it != m_lights[i].end(); ++it){
			app.Draw(*it);
		}
	}

	app.Draw(*m_OKButton);
	app.Draw(*m_resetButton);
}
