#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(500, 680), "Blocks!");
	window->setVerticalSyncEnabled(true);
	Game* game = new Game(window);

	while (game->window->isOpen())
	{
		sf::Event event;
		while (game->window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					game->window->close();
					break;
				}
				case sf::Event::KeyPressed:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Left:
						{
							game->moveLeft();
							break;
						}
						case sf::Keyboard::Right:
						{
							game->moveRight();
							break;
						}
						case sf::Keyboard::Space:
						{
							game->fastDrop();
							break;
						}
						case sf::Keyboard::Up:
						{
							game->rotate();
							break;
						}
						case sf::Keyboard::Escape:
						{
							game->window->close();
							break;
						}
						default:
						{
							std::cout << "DEBUG: No action found for key " << event.key.code << "." << std::endl;
							break;
						}
					}
				}
			}
		}

		game->Update();
		game->Draw();
	}
	delete game;
	return 0;
}