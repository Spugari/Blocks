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
	for (int i = 0; i < 220; i++)
	{
		int asd = i / 22;
		int bast = i % 22;
		delete gameArea[i / 22][i % 22];
	}

	for (blockCoords* a : activeBlock)
	{
		delete a;
	}
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

bool Game::dropActiveBlock()
{
	if (clock.getElapsedTime().asMilliseconds() >= 200)
	{
		clock.restart();

		//Check if the block can drop
		for (blockCoords* blocki : activeBlock)
		{
			//TODO: CHECK IF TILE BELOW IS PART OF CURRENT BLOCK
			//OR
			//DO NOT CHECK BELOW TILES THAT ARE ONTOP OF CURRENT BLOCK
			if (gameArea[blocki->x][blocki->y + 1]->getFillColor() != sf::Color::Transparent || (blocki->y + 1) > 21)
			{
				spawnBlock();
				return false;
			}
		}

		//Remove block from old location
		for (blockCoords* blocki : activeBlock)
		{
			gameArea[blocki->x][blocki->y]->setFillColor(sf::Color::Transparent);
			blocki->y += 1;
		}
		//After removing old block, draw the block at the new location (to prevent block tiles moving on top of each other)
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
		//First check if the block is at the left boundary
		if (blocki->x == 0)
			return false;
		
		//Check if there is free space to move the block
		bool cantMove = true;
		if (gameArea[blocki->x - 1][blocki->y]->getFillColor() != sf::Color::Transparent)
		{
			//Check if occupied tile is part of current block or not
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
	//First remove the old block
	for (blockCoords* blocki : activeBlock)
	{
		gameArea[blocki->x][blocki->y]->setFillColor(sf::Color::Transparent);
		blocki->x -= 1;
	}

	//After removing old block, draw the block at the new location (to prevent block tiles moving on top of each other)
	for (blockCoords* blocki : activeBlock)
	{
		gameArea[blocki->x][blocki->y]->setFillColor(activeColor);
	}
	return true;
}

bool Game::moveRight()
{
	//Check if the block can move right
	for (blockCoords* blocki : activeBlock)
	{
		//First check if the block is at the right boundary
		if (blocki->x == 9)
			return false;

		//Check if there is free space to move the block
		bool cantMove = true;
		if (gameArea[blocki->x + 1][blocki->y]->getFillColor() != sf::Color::Transparent)
		{
			//Check if occupied tile is part of current block or not
			for (blockCoords* otherBlock : activeBlock)
			{
				if (blocki == otherBlock)
					continue;
				else if (blocki->x + 1 == otherBlock->x && blocki->y == otherBlock->y)
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
	//First remove the old block
	for (blockCoords* blocki : activeBlock)
	{
		gameArea[blocki->x][blocki->y]->setFillColor(sf::Color::Transparent);
		blocki->x += 1;
	}

	//After removing old block, draw the block at the new location (to prevent block tiles moving on top of each other)
	for (blockCoords* blocki : activeBlock)
	{
		gameArea[blocki->x][blocki->y]->setFillColor(activeColor);
	}
	return true;
}