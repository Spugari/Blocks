#include "Highscores.h"

Highscores::Highscores()
{
}

void Highscores::AddHighscore(int score)
{
	std::vector<std::string> scores;
	std::string line;
	std::ifstream highscoresIn(highscoresPath);

	if (highscoresIn.is_open())
	{
		while (std::getline(highscoresIn, line))
			scores.push_back(line.substr(0,line.find_first_of(' ')));
	}

	highscoresIn.close();

	if (scores.empty())
	{
		scores.push_back(std::to_string(score));
	}
	else
	{
		bool added = false;
		for (std::vector<std::string>::iterator it = scores.begin(); it != scores.end(); it++)
		{
			if (std::stoi(*it) < score)
			{
				scores.insert(it, std::to_string(score));
				added = true;
				break;
			}
		}
		if (!added)
		{
			scores.push_back(std::to_string(score));
		}
	}

	std::fstream deleteScores;
	deleteScores.open(highscoresPath, std::ios::out | std::ios::trunc);
	deleteScores.close();

	std::ofstream highscoresOut(highscoresPath);
	if (highscoresOut.is_open())
	{
		int i = 0;
		for (std::vector<std::string>::iterator it = scores.begin(); it != scores.end(); it++, i++)
		{
			if (i >= HIGHSCORES_MAX)
			{
				break;
			}
			else
			{
				highscoresOut << *it + " lines\n";
			}
		}

		highscoresOut.close();
	}
	else
	{
		std::cout << "Error opening file \"Highscores.txt\"\n";
	}
}

std::vector<std::string> Highscores::GetHighscores()
{
	std::vector<std::string> scores;
	std::string line;
	std::ifstream highscoresIn(highscoresPath);

	if (highscoresIn.is_open())
	{
		while (std::getline(highscoresIn, line))
			scores.push_back(line);
	}
	else
	{
		std::cout << "Error opening file \"Highscores.txt\"\n";
	}
	highscoresIn.close();

	if (scores.empty())
	{
		scores.push_back("No highscores");
	}

	return scores;
}
