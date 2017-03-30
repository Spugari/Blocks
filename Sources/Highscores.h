#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

class Highscores
{
public:
	Highscores();
	void AddHighscore(int score);
	std::vector<std::string> GetHighscores();

private:
	const int HIGHSCORES_MAX = 10;
	std::string highscoresPath = "Resources/Highscores.txt";
};