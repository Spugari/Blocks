#pragma once

#include "Gameobject.h"

class Block : public GameObject
{
public:
	void Draw();
	Block(sf::RenderWindow* window);
	~Block();
	void DropOneLine();
	void MoveLeft();
	void MoveRight();

private:
	sf::RectangleShape* block;
};