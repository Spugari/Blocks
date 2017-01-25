#pragma once

#include <SFML\Graphics.hpp>
#include "Gameobject.h"

class Grid : public GameObject
{
public:
	Grid(sf::RenderWindow& window);
	void Draw();

private:
	sf::RectangleShape gridOutline;	
	sf::VertexArray grid;
};