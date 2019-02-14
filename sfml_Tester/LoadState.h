#pragma once
#include <string>

#include "GameState.h"
#include "Button.h"

class LoadState : public GameState
{
public:
	LoadState();
	~LoadState();

	// handle user inputs (keyboard/gamepad/mouse/etc)
	void handleInput(sf::Event& e, sf::RenderWindow& window);

	// render the window display: all rendering functions (like drawing images, fonts, etc. should be here)
	void render(sf::RenderWindow& window);

	// all non-rendering game logics/mechanics should be implemented here
	void update(float delta_t);

	// initialize instance
	void init();

	void cleanup();


private:
	sf::Texture saveTexture;
	sf::Sprite saveBackground;
	sf::Font settingsFont;
	sf::Text startNew;
	sf::Text returnState;
};