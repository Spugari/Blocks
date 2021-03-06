#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "Gameobject.h"
#include "Grid.h"
#include "Block.h"
#include "LineAnimation.h"
#include "HUD.h"
#include "Menu.h"
#include "Gamestate.h"
#include "Highscores.h"
#include <SFML/Audio.hpp>

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
		Z2,
		S,
		L,
		L2,
		I,
		T
	};

	GameState gameState = MainMenu;
	
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
	sf::Clock blockTimer;
	sf::Clock animTimer;
	sf::RectangleShape* gameArea[10][22];
	void drawGameArea();
	Grid* grid;
	HUD hud;
	bool spawnBlock();
	std::vector<blockCoords*> activeBlock;
	BlockType activeBlockType;
	sf::Color activeColor;
	void delFullLines();
	void deleteLine(int index);
	void dropField(int index);
	LineAnimation* lineAnim = nullptr;
	std::vector<int> linesToDelete;
	void checkGameOver();
	Menu menu;
	Soundmanager soundManager;
	Highscores highscore;
	void restart();
	sf::Texture logoTex;
	sf::Sprite logoSprite;
};
