#include "Water.h"
#include <iostream>

Water::Water(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize) : Element(x, y, type, elementSize)
{
	sf::Color v1 = sf::Color(39, 109, 171, 255);
	sf::Color v2 = sf::Color(44, 115, 179, 255);
	sf::Color v3 = sf::Color(35, 105, 167, 255);

	std::array<sf::Color, 3> colors = { v1, v2, v3 };

	int random = rand() % 3;

	setColor(colors[random]);

	_spreadFactor = 3;
}

void Water::update(Matrix* matrix)
{
	if (getMatrixY() == matrix->getHeight() - 1) return;

	if (matrix->getXY(getMatrixX(), getMatrixY() + 1) == nullptr)
	{
		matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX(), getMatrixY() + 1));
	}

	else if (getMatrixX() != (matrix->getWidth() - 1) && matrix->getXY(getMatrixX() + 1, getMatrixY() + 1) == nullptr)
	{
		matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() + 1, getMatrixY() + 1));
	}

	else if (getMatrixX() != 0 && matrix->getXY(getMatrixX() - 1, getMatrixY() + 1) == nullptr)
	{
		matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() - 1, getMatrixY() + 1));
	}

	else if (getMatrixX() != (matrix->getWidth() - 1) && matrix->getXY(getMatrixX() + 1, getMatrixY()) == nullptr)
	{
		for (std::uint16_t i = 0; i < _spreadFactor; i++)
		{
			if (getMatrixY() == matrix->getHeight() - 1) return;

			if (matrix->getXY(getMatrixX(), getMatrixY() + 1) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX(), getMatrixY() + 1));
			}

			if (getMatrixY() == matrix->getHeight() - 1) return;

			else if (getMatrixX() != (matrix->getWidth() - 1) && matrix->getXY(getMatrixX() + 1, getMatrixY() + 1) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() + 1, getMatrixY() + 1));
			}

			if (getMatrixY() == matrix->getHeight() - 1) return;

			else if (getMatrixX() != 0 && matrix->getXY(getMatrixX() - 1, getMatrixY() + 1) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() - 1, getMatrixY() + 1));
			}

			else if (getMatrixX() + 1 + i < matrix->getWidth() && matrix->getXY(getMatrixX() + 1 + i, getMatrixY()) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() + 1 + i, getMatrixY()));
			}
			else {
				break;
			}
		}
	}

	else if (getMatrixX() != 0 && matrix->getXY(getMatrixX() - 1, getMatrixY()) == nullptr)
	{
		for (std::uint16_t i = _spreadFactor; i > 0; i--)
		{
			if (getMatrixY() == matrix->getHeight() - 1) return;

			if (matrix->getXY(getMatrixX(), getMatrixY() + 1) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX(), getMatrixY() + 1));
			}

			if (getMatrixY() == matrix->getHeight() - 1) return;

			else if (getMatrixX() != (matrix->getWidth() - 1) && matrix->getXY(getMatrixX() + 1, getMatrixY() + 1) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() + 1, getMatrixY() + 1));
			}

			if (getMatrixY() == matrix->getHeight() - 1) return;

			else if (getMatrixX() != 0 && matrix->getXY(getMatrixX() - 1, getMatrixY() + 1) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() - 1, getMatrixY() + 1));
			}

			else if (getMatrixX() - 1 - i > 0 && matrix->getXY(getMatrixX() - 1 - i, getMatrixY()) == nullptr)
			{
				matrix->swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() - 1 - i, getMatrixY()));
			}
			else {
				break;
			}
		}
	}
}