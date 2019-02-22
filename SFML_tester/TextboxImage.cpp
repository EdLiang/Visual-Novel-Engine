#include "TextboxImage.h"

TextboxImage::TextboxImage()
	: ItemImage("assets", "textboxw.png", 0, 0)
{
	initText();
}

TextboxImage::TextboxImage(ifstream & file)
	:ItemImage(file)
{
	initText();

	int startPos = file.tellg();

	try {
		name = UTILITY->readFromBinaryFile(file);
		dialogue = UTILITY->readFromBinaryFile(file);

		file.read(reinterpret_cast<char *>(&dialogueTextColor.r), sizeof(dialogueTextColor.r));
		file.read(reinterpret_cast<char *>(&dialogueTextColor.g), sizeof(dialogueTextColor.g));
		file.read(reinterpret_cast<char *>(&dialogueTextColor.b), sizeof(dialogueTextColor.b));
		file.read(reinterpret_cast<char *>(&dialogueTextColor.a), sizeof(dialogueTextColor.a));

		file.read(reinterpret_cast<char *>(&dialogueTextOutlineColor.r), sizeof(dialogueTextOutlineColor.r));
		file.read(reinterpret_cast<char *>(&dialogueTextOutlineColor.g), sizeof(dialogueTextOutlineColor.g));
		file.read(reinterpret_cast<char *>(&dialogueTextOutlineColor.b), sizeof(dialogueTextOutlineColor.b));
		file.read(reinterpret_cast<char *>(&dialogueTextOutlineColor.a), sizeof(dialogueTextOutlineColor.a));

		file.read(reinterpret_cast<char *>(&nameTextColor.r), sizeof(nameTextColor.r));
		file.read(reinterpret_cast<char *>(&nameTextColor.g), sizeof(nameTextColor.g));
		file.read(reinterpret_cast<char *>(&nameTextColor.b), sizeof(nameTextColor.b));
		file.read(reinterpret_cast<char *>(&nameTextColor.a), sizeof(nameTextColor.a));

		file.read(reinterpret_cast<char *>(&nameTextOutlineColor.r), sizeof(nameTextOutlineColor.r));
		file.read(reinterpret_cast<char *>(&nameTextOutlineColor.g), sizeof(nameTextOutlineColor.g));
		file.read(reinterpret_cast<char *>(&nameTextOutlineColor.b), sizeof(nameTextOutlineColor.b));
		file.read(reinterpret_cast<char *>(&nameTextOutlineColor.a), sizeof(nameTextOutlineColor.a));
	}
	catch (exception e)
	{
		LOGGER->Log("TextboxImage", "Unable to read from file");
		file.seekg(startPos);
		loaded = false;
		throw;
	}

	setDisplay(name, dialogue);
	setAlpha(alpha);
}

void TextboxImage::serialize(ofstream & savefile) const
{
	ItemImage::serialize(savefile);

	UTILITY->writeToBinaryFile(savefile, name);
	UTILITY->writeToBinaryFile(savefile, dialogue);

	savefile.write(reinterpret_cast<const char *>(&dialogueTextColor.r), sizeof(dialogueTextColor.r));
	savefile.write(reinterpret_cast<const char *>(&dialogueTextColor.g), sizeof(dialogueTextColor.g));
	savefile.write(reinterpret_cast<const char *>(&dialogueTextColor.b), sizeof(dialogueTextColor.b));
	savefile.write(reinterpret_cast<const char *>(&dialogueTextColor.a), sizeof(dialogueTextColor.a));

	savefile.write(reinterpret_cast<const char *>(&dialogueTextOutlineColor.r), sizeof(dialogueTextOutlineColor.r));
	savefile.write(reinterpret_cast<const char *>(&dialogueTextOutlineColor.g), sizeof(dialogueTextOutlineColor.g));
	savefile.write(reinterpret_cast<const char *>(&dialogueTextOutlineColor.b), sizeof(dialogueTextOutlineColor.b));
	savefile.write(reinterpret_cast<const char *>(&dialogueTextOutlineColor.a), sizeof(dialogueTextOutlineColor.a));

	savefile.write(reinterpret_cast<const char *>(&nameTextColor.r), sizeof(nameTextColor.r));
	savefile.write(reinterpret_cast<const char *>(&nameTextColor.g), sizeof(nameTextColor.g));
	savefile.write(reinterpret_cast<const char *>(&nameTextColor.b), sizeof(nameTextColor.b));
	savefile.write(reinterpret_cast<const char *>(&nameTextColor.a), sizeof(nameTextColor.a));

	savefile.write(reinterpret_cast<const char *>(&nameTextOutlineColor.r), sizeof(nameTextOutlineColor.r));
	savefile.write(reinterpret_cast<const char *>(&nameTextOutlineColor.g), sizeof(nameTextOutlineColor.g));
	savefile.write(reinterpret_cast<const char *>(&nameTextOutlineColor.b), sizeof(nameTextOutlineColor.b));
	savefile.write(reinterpret_cast<const char *>(&nameTextOutlineColor.a), sizeof(nameTextOutlineColor.a));
}

void TextboxImage::setText(const std::string & s)
{
	dialogue = s;
	dialogueText.setString(dialogue);
}

void TextboxImage::setName(const std::string & s)
{
	name = s;
	nameText.setString(name);
}

void TextboxImage::setDisplay(const std::string & s_name, const std::string & s_dialogue)
{
	setText(s_dialogue);
	setName(s_name);
}

void TextboxImage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ItemImage::draw(target, states);
	target.draw(dialogueText, states);
	target.draw(nameText, states);
}

void TextboxImage::setTextboxColor(sf::Color color)
{
	this->color = color;
	this->color.a = alpha;
	sprite.setColor(color);
}

void TextboxImage::setAlpha(float alpha)
{
	ItemImage::setAlpha(alpha);

	dialogueTextColor.a = (sf::Uint8) alpha;
	dialogueTextOutlineColor.a = (sf::Uint8) alpha;
	dialogueText.setFillColor(dialogueTextColor);
	dialogueText.setOutlineColor(dialogueTextOutlineColor);

	nameTextColor.a = (sf::Uint8) alpha;
	nameTextOutlineColor.a = (sf::Uint8) alpha;
	nameText.setFillColor(nameTextColor);
	nameText.setOutlineColor(nameTextOutlineColor);
}

void TextboxImage::addAlpha(float alpha)
{
	ItemImage::addAlpha(alpha);

	dialogueTextColor.a += (sf::Uint8) alpha;
	dialogueTextOutlineColor.a += (sf::Uint8) alpha;
	dialogueText.setFillColor(dialogueTextColor);
	dialogueText.setOutlineColor(dialogueTextOutlineColor);

	nameTextColor.a += (sf::Uint8) alpha;
	nameTextOutlineColor.a += (sf::Uint8) alpha;
	nameText.setFillColor(nameTextColor);
	nameText.setOutlineColor(nameTextOutlineColor);
}

void TextboxImage::initText()
{
	dialogueTextOutlineColor = sf::Color(0, 0, 0);
	dialogueTextColor = sf::Color(255, 255, 255);
	dialogueFont = sf::Font();
	if (!dialogueFont.loadFromFile(GLOBAL->DisplayTextFont))
	{
		LOGGER->Log("TextboxImage", "Unable to load default font");
	}

	dialogueText.setFont(dialogueFont);
	dialogueText.setStyle(sf::Text::Regular);
	dialogueText.setFillColor(dialogueTextColor);
	dialogueText.setOutlineColor(dialogueTextOutlineColor);
	dialogueText.setOutlineThickness(3);
	dialogueText.setCharacterSize(32);
	dialogueText.setPosition(230.0f, 705.0f);

	nameTextOutlineColor = sf::Color(0, 0, 0);
	nameTextColor = sf::Color(255, 255, 255);
	nameFont = sf::Font();
	if (!nameFont.loadFromFile(GLOBAL->DisplayNameFont))
	{
		LOGGER->Log("TextboxImage", "Unable to load name font");
	}

	nameText.setFont(nameFont);
	nameText.setStyle(sf::Text::Bold);
	nameText.setFillColor(nameTextColor);
	nameText.setOutlineColor(nameTextOutlineColor);
	nameText.setOutlineThickness(2);
	nameText.setCharacterSize(32);
	nameText.setPosition(230.0f, 643.0f);
}

