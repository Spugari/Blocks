#include "HUD.h"

HUD::HUD(sf::RenderWindow* window)
{
	this->window = window;

	//Get the font
	font.loadFromFile("Resources/FreeMono.ttf");

	//Initialize line counter
	lineCounter.setFont(font);
	lineCounter.setPosition(315, 40);
	lineCounter.setCharacterSize(20);
	lineCounter.setFillColor(sf::Color::White);
	lineCounter.setString(std::to_string(clearedLines) + lineCounterString);

	//Initialize level counter
	levelCounter.setFont(font);
	levelCounter.setPosition(315, 70);
	levelCounter.setCharacterSize(20);
	levelCounter.setFillColor(sf::Color::White);
}

void HUD::AddClearedLines(int lines)
{
	clearedLines += lines;
}

void HUD::Update()
{
	//Update counter text
	lineCounter.setString(std::to_string(clearedLines) + lineCounterString);
	levelCounter.setString(levelCounterString + std::to_string(level));
}

void HUD::Draw()
{
	window->draw(lineCounter);
	window->draw(levelCounter);
}

void HUD::Reset()
{
	clearedLines = 0;
	level = 1;
}