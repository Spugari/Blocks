#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	//this->grid = new Grid(this->window);
	this->grid = new Grid(window);


	clock.restart();

	//Clear gamearea
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 10; j++)
		{
/*			sf::RectangleShape* temp = new sf::RectangleShape();
			temp->setFillColor(sf::Color::Transparent);
			temp->setSize(sf::Vector2f(30.0f, 30.0f));
			temp->setPosition(sf::Vector2f(10.0f + j * 30.0f, 10.0f + i * 30.0f));
			gameArea[i][j] = temp;*/
		}
	}
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
	this->grid->Draw();
	this->window->display();
}

void Game::Update()
{
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

void Game::DropActiveBlock()
{
}

void Game::drawGameArea()
{

}