#pragma once

#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD();
	void Update();
	void AddClearedLines(int lines);
	sf::Text* GetDrawable() { return &lineCounter; }

private:
	sf::Font font;
	sf::Text lineCounter;
	std::string lineCounterString = " lines cleared.";
	int clearedLines = 0;
};