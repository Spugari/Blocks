#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(sf::RenderWindow* window);
	sf::RenderWindow* window;
	virtual void Draw();

private:
};