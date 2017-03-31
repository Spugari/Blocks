#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* window, GameState& gameState, Highscores* scores, Soundmanager* soundManager) : gameState(gameState), scores(scores)
{
	this->window = window;
	this->soundManager = soundManager;

	//Get the font
	font.loadFromFile("Resources/FreeMono.ttf");

	//Initialize main menu
	playText.setFont(font);
	playText.setCharacterSize(60);
	playText.setStyle(sf::Text::Bold);
	playText.setFillColor(sf::Color::Red);
	playText.setString("Play!");
	playText.setPosition((500 - playText.getLocalBounds().width) / 2, 250);

	highscoreText.setFont(font);
	highscoreText.setPosition(20, 100);
	highscoreText.setCharacterSize(60);
	highscoreText.setStyle(sf::Text::Bold);
	highscoreText.setFillColor(sf::Color::Red);
	highscoreText.setString("Highscores");
	highscoreText.setPosition((500 - highscoreText.getLocalBounds().width) / 2, 350);

	exitText.setFont(font);
	exitText.setCharacterSize(60);
	exitText.setStyle(sf::Text::Bold);
	exitText.setFillColor(sf::Color::Red);
	exitText.setString("Exit");
	exitText.setPosition((500 - exitText.getLocalBounds().width) / 2, 450);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game over!");
	gameOverText.setPosition((500 - gameOverText.getLocalBounds().left - gameOverText.getLocalBounds().width) / 2, 200);

	gameOverLabel.setFont(font);
	gameOverLabel.setCharacterSize(20);
	gameOverLabel.setFillColor(sf::Color::Red);
	gameOverLabel.setString("Press enter to return to menu.");
	gameOverLabel.setPosition((500 - gameOverLabel.getLocalBounds().left - gameOverLabel.getLocalBounds().width) / 2, 275);
}

void Menu::Draw()
{
	if (gameState == MainMenu)
	{
		window->draw(playText);
		window->draw(highscoreText);
		window->draw(exitText);
	}
	else if (gameState == GameOver)
	{
		window->draw(gameOverText);
		window->draw(gameOverLabel);
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
		{
			soundManager->PlayMusic(false);
			gameState = Playing;
		}
		else if (checkHoverAndPressed(highscoreText))
			gameState = HighscoreScreen;
		else if (checkHoverAndPressed(exitText))
			window->close();
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
			soundManager->PlaySound("Click");
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

	int i = 1;
	for (std::string score : highscores)
	{
		sf::Text label;
		label.setFont(font);
		label.setCharacterSize(20);
		label.setFillColor(sf::Color::Red);
		label.setString(std::to_string(i) + ". " + score);
		
		if (highscoreLabels.empty())
			label.setPosition(195, 180);
		else
			label.setPosition(195, highscoreLabels.back().getPosition().y + highscoreLabels.back().getLocalBounds().height + 15);
		
		highscoreLabels.push_back(label);
		i++;
	}

	highscoreBackText.setFont(font);
	highscoreBackText.setCharacterSize(40);
	highscoreBackText.setString("Back"); 
	highscoreBackText.setPosition(500, 680);
	highscoreBackText.setPosition(500 - highscoreBackText.getLocalBounds().width - 20 - highscoreBackText.getLocalBounds().left, 680 -  highscoreBackText.getLocalBounds().height - 20 - highscoreBackText.getLocalBounds().top);
	highscoreBackText.setFillColor(sf::Color::Red);

	highscoresUpdated = true;
}