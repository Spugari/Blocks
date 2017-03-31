#pragma once

#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD(sf::RenderWindow* window);
	void Update();
	void AddClearedLines(int lines);
	sf::Text* GetDrawable() { return &lineCounter; }
	int GetLevel() { return level; }
	int GetLines() { return clearedLines; }
	void SetLevel(int level) { this->level = level; }
	void Draw();
	void Reset();

private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text lineCounter;
	sf::Text levelCounter;
	std::string lineCounterString = " lines cleared.";
	std::string levelCounterString = "Level: ";
	int clearedLines = 0;
	int level = 1;
};