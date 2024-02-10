#include "Stone.h"

Stone::Stone(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize) : Element(x, y, type, elementSize)
{
	sf::Color v1 = sf::Color(80, 80, 80, 255);
	sf::Color v2 = sf::Color(65, 65, 65, 255);
	sf::Color v3 = sf::Color(50, 50, 50, 255);

	std::array<sf::Color, 3> colors = { v1, v2, v3 };

	int random = rand() % 3;

	setColor(colors[random]);
}

void Stone::update(Matrix* matrix)
{
	return;
}