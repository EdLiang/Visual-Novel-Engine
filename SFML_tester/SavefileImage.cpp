#include "SavefileImage.h"

SavefileImage::SavefileImage()
	: Effect("SavefileImage")
{

}

SavefileImage::~SavefileImage()
{
}

void SavefileImage::setImage(const sf::Image & image)
{
	saveTex.create(image.getSize().x, image.getSize().y);
	saveTex.update(image);

	saveSprite.setTexture(saveTex);
	setToScale();
}

void SavefileImage::setString(const std::string & title)
{
	saveTitle = title;
	if (saveTitle.length() >= stringLength)
	{
		saveTitle = saveTitle.substr(0, stringLength-3);
		saveTitle += "...";
	}
	saveText.setString(saveTitle);
}

void SavefileImage::useDefaultSprite()
{
	if (!saveTex.loadFromFile("images/assets/nodata.png"))
	{
		LOGGER->Log("SavefileImage", "Unable to load images/assets/nodata.png");
	}
	saveTex.setSmooth(true);

	saveSprite.setTexture(saveTex);
	setToScale();
}

void SavefileImage::setPosition(int x, int y)
{
	bgSprite.setPosition(x, y);
	bgBoxSprite.setPosition(x - 15, y - 13);
	saveSprite.setPosition(x + borderSize, y + borderSize);
	saveText.setPosition(x + 260, y + 20);
}

bool SavefileImage::isClicked(bool reset)
{
	bool temp = clicked;
	if (reset)
	{
		clicked = false;
	}
	return temp;
}

bool SavefileImage::isPressed() const
{
	return pressed;
}

bool SavefileImage::isOnHover() const
{
	return hovered;
}

bool SavefileImage::onLoad()
{
	// initialize the empty text
	if (!font.loadFromFile(GLOBAL->UserInterfaceFont))
	{
		LOGGER->Log("SavefileImage", "Unable to load font!");
	}

	saveText.setFont(font);
	saveText.setStyle(sf::Text::Regular);
	saveText.setFillColor(sf::Color(0, 0, 0, 255));
	saveText.setCharacterSize(16);

	if (!bgUnselectedTex.loadFromFile(GLOBAL->AssetRoot + "savebox.png"))
	{
		LOGGER->Log("SavefileImage", "Unable to load images/assets/savebox.png");
	}
	bgUnselectedTex.setSmooth(true);
	if (!bgBoxUnselectedTex.loadFromFile(GLOBAL->AssetRoot + "SaveBoxBack.png"))
	{
		LOGGER->Log("SavefileImage", "Unable to load images/assets/SaveBoxBack.png");
	}
	bgBoxUnselectedTex.setSmooth(true);
	if (!bgBoxSelectedTex.loadFromFile(GLOBAL->AssetRoot + "savebox_selected.png"))
	{
		LOGGER->Log("SavefileImage", "Unable to load images/assets/savebox_selected.png");
	}
	bgBoxSelectedTex.setSmooth(true);

	bgSprite.setTexture(bgUnselectedTex);
	bgBoxSprite.setTexture(bgBoxUnselectedTex);

	return true;
}

void SavefileImage::onUpdate(float delta_t)
{

}

void SavefileImage::onDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(bgBoxSprite, states);
	target.draw(bgSprite, states);
	target.draw(saveSprite, states);
	target.draw(saveText, states);
}

void SavefileImage::onHandleInput(sf::Event & e, sf::RenderWindow & window)
{

	sf::Vector2f mousePosF = CONFIG->getCursorPosition(window);
	switch (e.type)
	{
		case sf::Event::MouseMoved:
		{
			if (bgSprite.getGlobalBounds().contains(mousePosF) || bgBoxSprite.getGlobalBounds().contains(mousePosF))
			{
				hovered = true;
				bgBoxSprite.setTexture(bgBoxSelectedTex);
			}
			else
			{
				hovered = false;
				bgBoxSprite.setTexture(bgBoxUnselectedTex);
			}
			break;
		}

		case sf::Event::MouseButtonPressed:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (bgSprite.getGlobalBounds().contains(mousePosF) || bgBoxSprite.getGlobalBounds().contains(mousePosF))
				{
					pressed = true;
				}
			}
			break;
		}

		case sf::Event::MouseButtonReleased:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (pressed)
				{
					pressed = false;
					clicked = true;
				}
			}
			break;
		}
	}
}

void SavefileImage::setToScale()
{
	float xScale = float(bgSprite.getLocalBounds().width - borderSize * 2) / float(saveSprite.getLocalBounds().width);
	float yScale = float(bgSprite.getLocalBounds().height - borderSize * 2) / float(saveSprite.getLocalBounds().height);

	saveSprite.setScale(xScale, yScale);
}
