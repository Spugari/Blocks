#include "HUD.h"

HUD::HUD()
{
	font.loadFromFile("arial.ttf");
	lineCounter.setFont(font);
	lineCounter.setPosition(350, 40);
	lineCounter.setCharacterSize(20);
	lineCounter.setFillColor(sf::Color::White);
	lineCounter.setString(std::to_string(clearedLines) + lineCounterString);
}

void HUD::AddClearedLines(int lines)
{
	clearedLines += lines;
}

void HUD::Update()
{
	lineCounter.setString(std::to_string(clearedLines) + lineCounterString);
}