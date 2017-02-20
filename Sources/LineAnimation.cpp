#include "LineAnimation.h"

LineAnimation::LineAnimation(std::vector<sf::RectangleShape*> tiles)
{
	this->tiles = tiles; 
	animTimer.restart();
}

void LineAnimation::Animate()
{
	if (animTimer.getElapsedTime() > sf::milliseconds(100))
	{
		animTimer.restart();

		if (!animationFinished)
		{
			if (animFrame % 2 == 0)
			{
				for (sf::RectangleShape* tile : tiles)
					tile->setFillColor(sf::Color::White);
			}
			else
			{
				for (sf::RectangleShape* tile : tiles)
					tile->setFillColor(sf::Color::Black);
			}

			animFrame++;
		}

		if (animFrame == 4)
			animationFinished = true;
	}
}