#include "Sand.h"
#include <iostream>

Sand::Sand(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize) : Element(x, y, type, elementSize)
{
	sf::Color v1 = sf::Color(204, 206, 58, 255);
	sf::Color v2 = sf::Color(186, 188, 45, 255);
	sf::Color v3 = sf::Color(206, 207, 94, 255);

	std::array<sf::Color, 3> colors = { v1, v2, v3 };
	
	int random = rand() % 3;

	setColor(colors[random]);

	_spreadFactor = 5;
}

void Sand::update(Matrix *matrix)
{
	if (getMatrixY() == matrix->getHeight() - 1) return;

	if (matrix->getXY(getMatrixX(), getMatrixY() + 1) == nullptr || (matrix->getXY(getMatrixX(), getMatrixY() + 1))->getType() == WATER)
	{
		matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX(), getMatrixY() + 1));
		return;
	}

	else if (getMatrixX() != (matrix->getWidth() - 1) && (matrix->getXY(getMatrixX() + 1, getMatrixY() + 1) == nullptr || (matrix->getXY(getMatrixX() + 1, getMatrixY() + 1))->getType() == WATER))
	{
		matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() + 1, getMatrixY() + 1));
		return;
	}

	else if (getMatrixX() != 0 && (matrix->getXY(getMatrixX() - 1, getMatrixY() + 1) == nullptr || (matrix->getXY(getMatrixX() - 1, getMatrixY() + 1))->getType() == WATER))
	{
		matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() - 1, getMatrixY() + 1));
		return;
	}

	/*else
		changeFallingState(false);*/
}