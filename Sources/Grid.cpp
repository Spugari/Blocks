#include "Grid.h"

Grid::~Grid()
{
	delete grid;
	delete gridOutline;
}

Grid::Grid(sf::RenderWindow* window) :  GameObject(window)
{
	gridOutline = new sf::RectangleShape();
	grid = new sf::VertexArray();

	gridOutline->setSize(sf::Vector2f(300, 660));
	gridOutline->setPosition(sf::Vector2f(10, 10));
	gridOutline->setOutlineColor(sf::Color::Red);
	gridOutline->setOutlineThickness(1.0f);
	gridOutline->setFillColor(sf::Color::Transparent);

	grid->setPrimitiveType(sf::Lines);

	//Vertical lines. Yes, I am an idiot and I like manual work.
	/*grid.append(sf::Vertex(sf::Vector2f(40.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(40.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(70.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(70.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(100.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(100.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(130.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(130.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(160.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(160.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(190.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(190.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(220.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(220.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(250.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(250.0f, 669.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(280.0f, 11.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(280.0f, 669.0f), sf::Color(255, 255, 255, 128)));*/

	//Let's clean that up :)

	int pos = 40;

	for (unsigned i = 0; i < 18; i++)
	{
		if (i % 2 == 0)
		{
			grid->append(sf::Vertex(sf::Vector2f(pos, 11.0f), sf::Color(255, 255, 255, 128)));
		}
		else
		{
			grid->append(sf::Vertex(sf::Vector2f(pos, 669.0f), sf::Color(255, 255, 255, 128)));
			pos += 30;
		}
	}

	//Horizontal lines
	/*grid.append(sf::Vertex(sf::Vector2f(11.0f, 40.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 40.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 70.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 70.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 100.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 100.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 130.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 130.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 160.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 160.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 190.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 190.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 220.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 220.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 250.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 250.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 280.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 280.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 310.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 310.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 340.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 340.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 370.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 370.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 400.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 400.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 430.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 430.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 460.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 460.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 490.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 490.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 520.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 520.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 550.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 550.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 580.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 580.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 610.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 610.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(11.0f, 640.0f), sf::Color(255, 255, 255, 128)));
	grid.append(sf::Vertex(sf::Vector2f(309.0f, 640.0f), sf::Color(255, 255, 255, 128)));*/

	pos = 40;

	for (unsigned i = 0; i < 42; i++)
	{
		if (i % 2 == 0)
		{
			grid->append(sf::Vertex(sf::Vector2f(11.0f, pos), sf::Color(255, 255, 255, 128)));
		}
		else
		{
			grid->append(sf::Vertex(sf::Vector2f(309.0f, pos), sf::Color(255, 255, 255, 128)));
			pos += 30;
		}
	}
}

void Grid::Draw()
{
	this->window->draw(*gridOutline);
	this->window->draw(*grid);

	//printf("Vertex %d\n", grid.getVertexCount());
}