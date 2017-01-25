#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game* game = new Game();

	while (game->window->isOpen())
	{
		sf::Event event;
		while (game->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game->window->close();
		}

		game->Draw();
	}
	return 0;
}