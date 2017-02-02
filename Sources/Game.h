#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "Gameobject.h"
#include "Grid.h"
#include "Block.h"

class Game
{
public:

	Game(sf::RenderWindow* window);
	~Game();

	sf::RenderWindow* window; // (sf::VideoMode(1280, 720), "SFML works!");
	/** Subscribe object's draw function to be drawn. */
	/** Unsubscribe a draw function (for example when a object is deleted, the object's draw function is unsubscribed) */
	/** Calls all subscribed draw functions */
	void Draw();
	void Update();

private:

	void DropActiveBlock();

	//std::map<unsigned, GameObject*> drawnObjects;
	sf::Clock clock;
	sf::RectangleShape* gameArea[10][22];
	void drawGameArea();
	Grid* grid;
};
