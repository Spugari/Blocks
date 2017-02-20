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

	struct blockCoords
	{
		blockCoords(int x, int y) { this->x = x; this->y = y; }
		int x;
		int y;

		bool operator==(const blockCoords& b)
		{
			if (b.x == this->x && b.y == this->y)
				return true;
			return false;
		}
	};

	enum BlockType
	{
		Z,
		S,
		L,
		L2,
		I
	};

	Game(sf::RenderWindow* window);
	~Game();

	sf::RenderWindow* window; // (sf::VideoMode(1280, 720), "SFML works!");
	/** Subscribe object's draw function to be drawn. */
	/** Unsubscribe a draw function (for example when a object is deleted, the object's draw function is unsubscribed) */
	/** Calls all subscribed draw functions */
	void Draw();
	void Update();
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	void fastDrop();
	void rotate();
	bool canRotate(std::vector<blockCoords*> block);

private:

	bool dropActiveBlock(int time);

	//std::map<unsigned, GameObject*> drawnObjects;
	sf::Clock clock;
	sf::RectangleShape* gameArea[10][22];
	void drawGameArea();
	Grid* grid;
	bool spawnBlock();
	std::vector<blockCoords*> activeBlock;
	BlockType activeBlockType;
	sf::Color activeColor;
	void delFullLines();
	void deleteLine(int index);
	void dropField(int index);
};
