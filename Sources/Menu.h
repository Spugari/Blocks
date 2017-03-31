#pragma once
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "Highscores.h"
#include "Soundmanager.h"

class Menu
{
public:
	Menu(sf::RenderWindow* window, GameState& gameState, Highscores* scores, Soundmanager* soundManager);
	void Draw();
	void Update();

private:
	sf::Font font;
	sf::Text playText;
	sf::Text highscoreText;
	sf::Text gameOverText;
	sf::Text gameOverLabel;
	sf::Text highscoreBackText;
	sf::Text exitText;
	sf::RenderWindow* window;
	GameState& gameState;
	bool checkHoverAndPressed(sf::Text& text);
	bool highscoresUpdated = false;
	Highscores* scores;
	std::vector<std::string> highscores;
	std::vector<sf::Text> highscoreLabels;
	void updateHighscores();
	Soundmanager* soundManager;
};