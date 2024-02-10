#include "Statistics.h"
#include <string>

Statistics::Statistics()
{
	_elementsCount = 0;
	_verticesCount = 0;
	_font = sf::Font();
	_font.loadFromFile("Silkscreen.ttf");
}

void Statistics::setVerticesCount(std::uint32_t verticesCount)
{
	_verticesCount = verticesCount;
}

void Statistics::setElementsCount(std::uint16_t elementsCount)
{
	_elementsCount = elementsCount;
}

void Statistics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text vertices = sf::Text();
	sf::Text elements = sf::Text();

	vertices.setFont(_font);
	vertices.setCharacterSize(14);
	vertices.setPosition(sf::Vector2f(5, 5));
	vertices.setString("Vertices: " + std::to_string(_verticesCount));

	elements.setFont(_font);
	elements.setCharacterSize(14);
	elements.setPosition(sf::Vector2f(5, 25));
	elements.setString("Elements: " + std::to_string(_elementsCount));

	target.draw(vertices);
	target.draw(elements);
}