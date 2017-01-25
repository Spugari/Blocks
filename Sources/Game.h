#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>
#include "Gameobject.h"
#include "Grid.h"

class Game
{
public:

	Game();
	~Game();

	sf::RenderWindow* window; // (sf::VideoMode(1280, 720), "SFML works!");
	/** Subscribe object's draw function to be drawn. */
	bool DrawSubscribe(GameObject* asset, unsigned z);
	/** Unsubscribe a draw function (for example when a object is deleted, the object's draw function is unsubscribed) */
	bool DrawUnsubscribe(unsigned z);
	/** Calls all subscribed draw functions */
	void Draw();

private:

	void Update();

	std::map<unsigned, GameObject*> drawnObjects;
};
