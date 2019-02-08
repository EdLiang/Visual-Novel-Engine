#include "Button.h"

bool Button::onLoad()
{
	if (!texture.loadFromFile(texPath))
	{
		LOGGER->Log("Button", "Error loading button texture");
		return false;
	}
	sprite.setTexture(texture);

	hasShader = false;
	if (vertShaderPath != "" && fragShaderPath != "")
	{
		if (!shader.loadFromFile(vertShaderPath, fragShaderPath))
		{
			LOGGER->Log("Button", "Error loading vert/frag shaders");
		}
		else
		{
			hasShader = true;
		}
	}
	else if (vertShaderPath != "")
	{
		if (!shader.loadFromFile(vertShaderPath, sf::Shader::Vertex))
		{
			LOGGER->Log("Button", "Error loading vert shader");
		}
		else
		{
			hasShader = true;
		}
	}
	else if (fragShaderPath != "")
	{
		if (!shader.loadFromFile(fragShaderPath, sf::Shader::Fragment))
		{
			LOGGER->Log("Button", "Error loading frag shader");
		}
		else
		{
			hasShader = true;
		}
	}

	return true;
}

void Button::onUpdate(float delta_t)
{
}

void Button::onDraw(sf::RenderTarget & target, sf::RenderStates states)
{
	if (hasShader)
	{
		states.shader = &shader;
	}
	target.draw(sprite, states);
}

void Button::handleInput(sf::Event & e, sf::RenderWindow & window)
{
}
