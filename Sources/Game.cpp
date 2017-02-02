#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	//this->grid = new Grid(this->window);
	this->grid = new Grid(window);


	clock.restart();

	//Clear gamearea


	//Voi vittu matti

	for (int i = 0; i < 220; i++)
	{
		gameArea[i/22][i%22] = new sf::RectangleShape();
		gameArea[i / 22][i % 22]->setFillColor(sf::Color::Transparent);
		gameArea[i / 22][i % 22]->setSize(sf::Vector2f(30.0f, 30.0f));
		gameArea[i / 22][i % 22]->setPosition(sf::Vector2f(10.0f + (i / 22) * 30.0f, 10.0f + (i%22) * 30.0f));
	}

	/*for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gameArea[i][j] = new sf::RectangleShape();
			gameArea[i][j]->setFillColor(sf::Color::Transparent);
			gameArea[i][j]->setSize(sf::Vector2f(30.0f, 30.0f));
			gameArea[i][j]->setPosition(sf::Vector2f(10.0f + j * 30.0f, 10.0f + i * 30.0f));
		}
	}*/

	spawnBlock();
}

Game::~Game()
{
/*	for (int i = 0; i < 220; i++)
	{
		int asd = i / 22;
		int bast = i % 22;
		delete gameArea[i / 22][i % 22];
	}*/
}

void Game::Draw()
{
	this->window->clear();

	for (int i = 0; i < 220; i++)
	{
		window->draw((*gameArea[i / 22][i % 22]));
	}

	this->grid->Draw();
	this->window->display();
}

void Game::Update()
{
	if (!dropActiveBlock())
		std::cout << "Could not drop active block!" << std::endl;
}

/*bool Game::DrawSubscribe(GameObject* asset, unsigned z)
{
	try
	{
		auto returnValue = drawnObjects.insert(std::pair<unsigned, GameObject*>(z, asset));
		if (!returnValue.second)
		{
			std::cout << "Draw function with z index " << z << " alredy exists." << std::endl;
			throw 1;
		}
	}
	catch (int e)
	{
		switch (e)
		{
			case 1:
			{
				std::cout << "Tried to subscribe two draw functions with the same name" << std::endl;
				exit(0);
				break;
			}
			default:
			{
				std::cout << "Unspecified error." << std::endl;
				exit(0);
			}
		}
	}

	return true;
}*/

bool Game::dropActiveBlock()
{
	if (clock.getElapsedTime().asMilliseconds() >= 200)
	{
		clock.restart();

		//Check if the block can drop
		for (blockCoords* blocki : activeBlock)
		{
			if (gameArea[blocki->x][blocki->y + 1]->getFillColor() != sf::Color::Transparent || (blocki->y + 1) > 21)
			{
				spawnBlock();
				return false;
			}
		}

		for (blockCoords* blocki : activeBlock)
		{
			gameArea[blocki->x][blocki->y]->setFillColor(sf::Color::Transparent);
			blocki->y += 1;
		}
		for (blockCoords* blocki : activeBlock)
		{
			gameArea[blocki->x][blocki->y]->setFillColor(activeColor);
		}
	}
	return true;
}

bool Game::spawnBlock()
{
	activeBlock.clear();
	activeColor = sf::Color::Green;

	for (int i = 3; i <= 6; i++)
	{
		gameArea[i][0]->setFillColor(sf::Color::Green);
		activeBlock.push_back(new blockCoords(i,0));
	}

	return true;
}

bool Game::moveLeft()
{
	//Check if the block can move left
	for (blockCoords* blocki : activeBlock)
	{
		if (blocki->x == 0)
			return false;
		
		bool cantMove = true;
		if (gameArea[blocki->x - 1][blocki->y]->getFillColor() != sf::Color::Transparent)
		{
			for (blockCoords* otherBlock : activeBlock)
			{
				if (blocki == otherBlock)
					continue;
				else if (blocki->x - 1 == otherBlock->x && blocki->y == otherBlock->y)
				{
					cantMove = false;
					break;
				}
			}
			if (cantMove)
				return false;
		}
	}

	//The block can move left, so lets move it!
	for (blockCoords* blocki : activeBlock)
	{
		gameArea[blocki->x][blocki->y]->setFillColor(sf::Color::Transparent);
		blocki->x -= 1;
	}

	for (blockCoords* blocki : activeBlock)
	{
		gameArea[blocki->x][blocki->y]->setFillColor(activeColor);
	}
	return true;
}