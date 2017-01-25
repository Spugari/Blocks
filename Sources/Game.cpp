#include "Game.h"

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Blocks!");

	if (!DrawSubscribe(new Grid(*window), 1))
	{
		std::cout << "Failed to subscribe object with z index " << 1 << " ." << std::endl;
	}
}

void Game::Draw()
{
	window->clear();

	for (auto pair : drawnObjects)
	{
		(*pair.second).Draw();
	}

	window->display();
}

bool Game::DrawSubscribe(GameObject* asset, unsigned z)
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
}