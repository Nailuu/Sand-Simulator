#include "Selector.h"

Selector::Selector(std::uint16_t w_width, std::uint16_t w_height)
{
	_font = sf::Font();
	_font.loadFromFile("Silkscreen.ttf");

	_selectedElement = 0;

	_windowWidth = w_width;
	_windowHeight = w_height;

	_elements = std::vector<std::pair<ElementType, sf::Texture>>();

	sf::Texture sand;
	sand.loadFromFile("sand.jpeg");
	_elements.push_back(std::pair<ElementType, sf::Texture>(SAND, sand));

	sf::Texture water;
	water.loadFromFile("water.jpeg");
	_elements.push_back(std::pair<ElementType, sf::Texture>(WATER, water));

	sf::Texture stone;
	stone.loadFromFile("stone.jpeg");
	_elements.push_back(std::pair<ElementType, sf::Texture>(STONE, stone));
}

ElementType Selector::getSelectedElement() const
{
	return _elements[_selectedElement].first;
}

void Selector::changeSelection(std::int16_t direction)
{
	if (direction > 0 && _selectedElement - 1 >= 0)
		_selectedElement--;
	else if (direction < 0 && _selectedElement + 1 < _elements.size())
		_selectedElement++;
}

void Selector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::uint16_t spriteSize = 24;
	std::uint16_t gap = 12;
	std::uint16_t selectionBorderWidth = 4;

	for (std::uint16_t x = 0; x < _elements.size(); x++)
	{
		sf::Sprite sprite;
		sprite.setTexture(_elements[x].second);
		sprite.setScale(sf::Vector2f(0.75, 0.75));
		sprite.setPosition(sf::Vector2f(_windowWidth - spriteSize - gap, (spriteSize * x) + gap * (x + 1)));

		if (x == _selectedElement)
		{
			sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color::White);

			rectangle.setPosition(sf::Vector2f(sprite.getPosition().x - selectionBorderWidth, sprite.getPosition().y - selectionBorderWidth));

			rectangle.setSize(sf::Vector2f(spriteSize + (selectionBorderWidth * 2), spriteSize + (selectionBorderWidth * 2)));

			target.draw(rectangle);
		}

		target.draw(sprite);
	}
}