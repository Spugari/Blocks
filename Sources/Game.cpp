#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	//this->grid = new Grid(this->window);
	this->grid = new Grid(window);


	clock.restart();

	//Clear gamearea

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
			//I-block
			activeBlockType = BlockType::I;

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
			//I-block
			activeBlockType = BlockType::I;

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
			//Z-block
			activeBlockType = BlockType::Z;

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
			//Box
			activeBlockType = BlockType::S;

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

bool Game::moveUp()
{
	std::vector<blockCoords*> newCoords;

	for (blockCoords* tile : activeBlock)
	{
		newCoords.push_back(new blockCoords(tile->x, tile->y - 1));
	}

	/*for (blockCoords* tile : newCoords)
	{
		if (gameArea[tile->x][tile->y]->getFillColor() != sf::Color::Transparent)
		{
			return false;
		}
	}*/

	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);
		tile->y -= 1;
	}

	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);
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

void Game::rotate()
{
	//Center contains the tile the block rotates around.
	blockCoords* center;

	switch (activeBlockType)
	{
		case BlockType::S:
		{
			//No need to rotate square block.
			return;
		}
		case BlockType::Z:
		{
			center = activeBlock[2];
			break;
		}
		case BlockType::I:
		{
			center = activeBlock[2];
			break;
		}
		default:
		{
			std::cout << "WARNING: Unknown BlockType in Game::rotate()!" << std::endl;
			return;
		}
	}

	std::vector<blockCoords*> newCoords;
	std::vector<blockCoords*> testCoords;

	//New tile positions
	newCoords.push_back(new blockCoords(activeBlock[0]->y + center->x - center->y, center->x + center->y - activeBlock[0]->x));
	newCoords.push_back(new blockCoords(activeBlock[1]->y + center->x - center->y, center->x + center->y - activeBlock[1]->x));
	newCoords.push_back(new blockCoords(activeBlock[2]->x, activeBlock[2]->y));
	newCoords.push_back(new blockCoords(activeBlock[3]->y + center->x - center->y, center->x + center->y - activeBlock[3]->x));

	for (blockCoords* tile : newCoords)
		testCoords.push_back(new blockCoords(tile->x, tile->y));

	//Clear old block
	for (blockCoords* tile : activeBlock)
		gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);

	//Check if new pos is valid
	if (canRotate(newCoords))
		return;

	for (blockCoords* tile : newCoords)
	{
		if (tile->x < 0)
		{
			for (blockCoords* asd : testCoords)
				asd->x += 1;

			if (canRotate(testCoords))
				return;
		}

		if (tile->x > 9)
		{
			for (blockCoords* asd : testCoords)
				asd->x -= 1;

			if (canRotate(testCoords))
				return;
		}
	}

	//Try one or two block up
	for (int i = 0; i < 2; i++)
	{
		for (blockCoords* tile : testCoords)
			tile->y -= 1;

		if (canRotate(testCoords))
			return;
	}

	//Could not rotate the block, place it back to old place
	for (blockCoords* tile : activeBlock)
		gameArea[tile->x][tile->y]->setFillColor(activeColor);

	/*if (!canRotate(newCoords))
	{
		for (blockCoords* tile : newCoords)
			tile->x += 1;

		if (!canRotate(newCoords))
		{
			for (blockCoords* tile : newCoords)
				tile->x -= 2;

			if (!canRotate(newCoords))
			{
				for (blockCoords* tile : newCoords)
					tile->x += 1;

				while (!canRotate)
				{

				}
			}
		}
	}*/

	/*//What do if the rotated block doesn't fit :(
	if (!canRotate)
	{
		canRotate = true;
		//First try moving the block right (yes it is right biased)
		for (blockCoords* tile : newCoords)
		{
			if (tile->x + 1 > 9 || gameArea[tile->x + 1][tile->y]->getFillColor() != sf::Color::Transparent)
			{
				canRotate = false;
				break;
			}
		}

		//Couldn't go right, lets try left
		if (!canRotate)
		{

		}
	}*/

	/*for (blockCoords* tile : newCoords)
	{
		bool sameBlock = false;
		for (blockCoords* asd : activeBlock)
		{
			if (asd->x == tile->x && asd->y == tile->y)
			{
				sameBlock = true;
				break;
			}
		}
		if (sameBlock)
			continue;

		if (tile->x < 0)
		{
			if (!moveRight())
				moveUp();
			rotate();
			return;
		}
		else if (tile->x > 9)
		{
			if (!moveLeft())
				moveUp();
			rotate();
			return;
		}
		else if (gameArea[tile->x][tile->y]->getFillColor() != sf::Color::Transparent)
		{
			if (!moveRight())
				if (!moveLeft())
					moveUp();
			rotate();
			return;
			//moveUp();
			//rotate();
			//return;
		}
	}*/
	
	/*//Potential memory leak?
	for (blockCoords* tile : activeBlock)
	{
		gameArea[tile->x][tile->y]->setFillColor(sf::Color::Transparent);
	}

	activeBlock.clear();
	for (blockCoords* tile : newCoords)
	{
		gameArea[tile->x][tile->y]->setFillColor(activeColor);
		activeBlock.push_back(tile);
	}*/
}

bool Game::canRotate(std::vector<blockCoords*> block)
{
	//Check if there is anything blocking the rotation
	for (blockCoords* tile : block)
	{
		if (tile->x < 0)
			return false;
		else if (tile->x > 9)
			return false;
		else if (tile->y > 21)
			return false;
		else if (gameArea[tile->x][tile->y]->getFillColor() != sf::Color::Transparent)
			return false;
	}
	
	//Set the block in it's new place if it can rotate
	activeBlock.clear();
	for (blockCoords* tile : block)
	{
		gameArea[tile->x][tile->y]->setFillColor(activeColor);
		activeBlock.push_back(tile);
	}

	return true;
}

/*
x2 = (y1 + px - py)

y2 = (px + py - x1 - q)
To rotate the opposite direction:

x2 = (px + py - y1 - q)

y2 = (x1 + py - px)
*/