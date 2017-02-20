#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class LineAnimation
{
public:
	LineAnimation(std::vector<sf::RectangleShape*> tiles);
	void Animate();
	bool IsFinished() { return animationFinished; }

private:
	std::vector<sf::RectangleShape*> tiles;
	bool animationFinished = false;
	sf::Clock animTimer;
	int animFrame = 0;
};