#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* window, GameState& gameState, Highscores* scores) : gameState(gameState), scores(scores)
{
	this->window = window;

	//Get the font
	font.loadFromFile("Resources/FreeMono.ttf");

	//Initialize main menu
	playText.setFont(font);
	playText.setPosition(20, 40);
	playText.setCharacterSize(40);
	playText.setFillColor(sf::Color::Red);
	playText.setString("Play!");

	highscoreText.setFont(font);
	highscoreText.setPosition(20, 100);
	highscoreText.setCharacterSize(40);
	highscoreText.setFillColor(sf::Color::Red);
	highscoreText.setString("Highscores");

	gameOverText.setFont(font);
	gameOverText.setPosition(20, 40);
	gameOverText.setCharacterSize(20);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game over!\nPress enter to return to menu.");
}

void Menu::Draw()
{
	if (gameState == MainMenu)
	{
		window->draw(playText);
		window->draw(highscoreText);
	}
	else if (gameState == GameOver)
	{
		window->draw(gameOverText);
	}
	else if (gameState == HighscoreScreen)
	{
		for (sf::Text label : highscoreLabels)
		{
			window->draw(label);
			window->draw(highscoreBackText);
		}
	}
}

void Menu::Update()
{
	if (gameState == MainMenu)
	{
		if (checkHoverAndPressed(playText))
			gameState = Playing;
		else if (checkHoverAndPressed(highscoreText))
			gameState = HighscoreScreen;
	}

	if (gameState == HighscoreScreen)
	{
		if (!highscoresUpdated)
			updateHighscores();

		if (checkHoverAndPressed(highscoreBackText))
		{
			gameState = MainMenu;
			highscoresUpdated = false;
		}
	}
}

bool Menu::checkHoverAndPressed(sf::Text& text)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::IntRect bounds = sf::IntRect(text.getPosition().x + text.getLocalBounds().left, text.getPosition().y + text.getLocalBounds().top, text.getLocalBounds().width, text.getLocalBounds().height);

	//Check if player is hovering over the text
	if (mousePos.x >= bounds.left && mousePos.y >= bounds.top
		&& mousePos.x <= bounds.left + bounds.width && mousePos.y <= bounds.top + bounds.height)
	{
		text.setFillColor(sf::Color::Green);

		//Check if player pressed the text
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}

		return false;
	}
	else
	{
		text.setFillColor(sf::Color::Red);
		return false;
	}
}

void Menu::updateHighscores()
{
	highscores.clear();
	highscoreLabels.clear();
	highscores = scores->GetHighscores();

	for (std::string score : highscores)
	{
		sf::Text label;
		label.setFont(font);
		label.setCharacterSize(20);
		label.setFillColor(sf::Color::Red);
		label.setString(score);
		
		if (highscoreLabels.empty())
			label.setPosition(20, 20);
		else
			label.setPosition(20, highscoreLabels.back().getPosition().y + highscoreLabels.back().getLocalBounds().height + 15);
		
		highscoreLabels.push_back(label);
	}

	highscoreBackText.setFont(font);
	highscoreBackText.setCharacterSize(40);
	highscoreBackText.setString("Back"); 
	highscoreBackText.setPosition(500, 680);
	highscoreBackText.setPosition(500 - highscoreBackText.getLocalBounds().width - 20 - highscoreBackText.getLocalBounds().left, 680 -  highscoreBackText.getLocalBounds().height - 20 - highscoreBackText.getLocalBounds().top);
	highscoreBackText.setFillColor(sf::Color::Red);

	highscoresUpdated = true;
}