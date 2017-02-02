#include "Block.h"

Block::Block(sf::RenderWindow* window) : GameObject(window)
{
	block = new sf::RectangleShape();
	block->setSize(sf::Vector2f(120, 30));
	block->setPosition(sf::Vector2f(40, 40));
	block->setFillColor(sf::Color::Green);
}

Block::~Block()
{
	delete block;
}

void Block::Draw()
{
	window->draw(*block);
}

void Block::DropOneLine()
{
	block->setPosition(sf::Vector2f(block->getPosition() + sf::Vector2f(0, 30)));
}

void Block::MoveLeft()
{
	block->setPosition(sf::Vector2f(block->getPosition() + sf::Vector2f(-30, 0)));
}

void Block::MoveRight()
{
	block->setPosition(sf::Vector2f(block->getPosition() + sf::Vector2f(30, 0)));
}