#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(500, 680), "Blocks!");

	Game* game = new Game(window);

	while (game->window->isOpen())
	{
		sf::Event event;
		while (game->window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				game->window->close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
				game->moveLeft();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
				game->moveRight();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				game->fastDrop();
			if (event.type == sf::Event::Closed)
				game->window->close();
		}

		game->Update();
		game->Draw();
	}
	delete game;
	return 0;
}