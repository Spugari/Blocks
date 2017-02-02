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
	if (!dropActiveBlock(200))
	{
		std::cout << "Could not drop active block!" << std::endl;
		delFullLines();
		spawnBlock();
	}
}

bool Game::dropActiveBlock(int time)
{
	if (clock.getElapsedTime().asMilliseconds() >= time)
	{
		clock.restart();

		//Check if the block can drop
		for (blockCoords* tile : activeBlock)
		{
			if ((tile->y + 1) > 21)
				return false;

			for (blockCoords* tile : activeBlock)
			{
				//Check if there is free space to move the block
				bool cantMove = true;
				if (gameArea[tile->x][tile->y + 1]->getFillColor() != sf::Color::Transparent)
				{
					//Check if occupied tile is part of current block or not
					for (blockCoords* otherBlock : activeBlock)
					{
						if (tile == otherBlock)
							continue;
						else if (tile->x == otherBlock->x && tile->y + 1 == otherBlock->y)
						{
							cantMove = false;
							break;
						}
					}
					if (cantMove)
						return false;
				}
			}
		}

		//Remove block from old location
		for (blockCoords* tile : activeBlock)
		{
			gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);
			tile->y += 1;
		}
		//After removing old block, draw the block at the new location (to prevent block tiles moving on top of each other)
		for (blockCoords* tile : activeBlock)
		{
			gameArea[tile->x][tile->y]->setFillColor(activeColor);
		}
	}
	return true;
}

bool Game::spawnBlock()
{
	activeBlock.clear();

	switch (clock.getElapsedTime().asMicroseconds() % 4)
	{
		case 0:
		{
			for (int i = 3; i <= 6; i++)
			{
				activeColor = sf::Color::Green;
				gameArea[i][0]->setFillColor(sf::Color::Green);
				activeBlock.push_back(new blockCoords(i, 0));
			}
			break;
		}
		case 1:
		{
			for (int i = 0; i <= 3; i++)
			{
				activeColor = sf::Color::Green;
				gameArea[4][i]->setFillColor(activeColor);
				activeBlock.push_back(new blockCoords(4, i));
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < 2; i++)
			{
				activeColor = sf::Color::Red;
				gameArea[3 + i][i]->setFillColor(activeColor);
				activeBlock.push_back(new blockCoords(3 + i, i));
				gameArea[4 + i][i]->setFillColor(activeColor);
				activeBlock.push_back(new blockCoords(4 + i, i));
			}
			break;
		}
		case 3:
		{
			for (int i = 0; i < 2; i++)
			{
				activeColor = sf::Color::Blue;
				gameArea[3][i]->setFillColor(activeColor);
				activeBlock.push_back(new blockCoords(3, i));
				gameArea[4][i]->setFillColor(activeColor);
				activeBlock.push_back(new blockCoords(4, i));
			}
		}
	}
	return true;
}

bool Game::moveLeft()
{
	//Check if the block can move left
	for (blockCoords* tile : activeBlock)
	{
		//First check if the block is at the left boundary
		if (tile->x == 0)
			return false;
		
		//Check if there is free space to move the block
		bool cantMove = true;
		if (gameArea[tile->x - 1][tile->y]->getFillColor() != sf::Color::Transparent)
		{
			//Check if occupied tile is part of current block or not
			for (blockCoords* otherBlock : activeBlock)
			{
				if (tile == otherBlock)
					continue;
				else if (tile->x - 1 == otherBlock->x && tile->y == otherBlock->y)
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
	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);
		tile->x -= 1;
	}

	//After removing old block, draw the block at the new location (to prevent block tiles moving on top of each other)
	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(activeColor);
	}
	return true;
}

bool Game::moveRight()
{
	//Check if the block can move right
	for (blockCoords* tile : activeBlock)
	{
		//First check if the block is at the right boundary
		if (tile->x == 9)
			return false;

		//Check if there is free space to move the block
		bool cantMove = true;
		if (gameArea[tile->x + 1][tile->y]->getFillColor() != sf::Color::Transparent)
		{
			//Check if occupied tile is part of current block or not
			for (blockCoords* otherBlock : activeBlock)
			{
				if (tile == otherBlock)
					continue;
				else if (tile->x + 1 == otherBlock->x && tile->y == otherBlock->y)
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
	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);
		tile->x += 1;
	}

	//After removing old block, draw the block at the new location (to prevent block tiles moving on top of each other)
	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(activeColor);
	}
	return true;
}

void Game::fastDrop()
{
	while (dropActiveBlock(0));
	delFullLines();
	spawnBlock();
}

void Game::delFullLines()
{
	std::vector<int> fullLines;

	for (int i = 0; i < 22; i++)
	{
		bool fullLine = true;
		for (int j = 0; j < 10; j++)
		{
			if (gameArea[j][i]->getFillColor() == sf::Color::Transparent)
			{
				fullLine = false;
				break;
			}
		}
		if (fullLine)
			fullLines.push_back(i);
	}

	if (fullLines.size() == 0)
		return;

	for (int i : fullLines)
	{
		deleteLine(i);
		dropField(i);
	}
}

void Game::deleteLine(int index)
{
	for (int i = 0; i < 10; i++)
	{
		gameArea[i][index]->setFillColor(sf::Color::Transparent);
	}
}

void Game::dropField(int index)
{
	for (int i = index - 1; i >= 0; i--)
	{
		for (int j = 0; j < 10; j++)
		{
			gameArea[j][i + 1]->setFillColor(gameArea[j][i]->getFillColor());
			gameArea[j][i]->setFillColor(sf::Color::Transparent);
		}
	}
}