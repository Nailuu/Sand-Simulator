#include "Element.h"

Element::Element(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize)
{
	_elementSize = elementSize;
	_matrixX = (x - (x % _elementSize)) / _elementSize;
	_matrixY = (y - (y % _elementSize)) / _elementSize;
	_windowX = x - (x % _elementSize);
	_windowY = y - (y % _elementSize);
	_type = type;
	_isFalling = true;
}

void Element::set(std::uint16_t x, std::uint16_t y, std::uint16_t m_height)
{
	_matrixX = x;
	_matrixY = y;

	_windowX = x * _elementSize;
	_windowY = y * _elementSize;

	if (y == m_height - 1)
		changeFallingState(false);
}

std::uint16_t Element::getMatrixX() const
{
	return _matrixX;
}

std::uint16_t Element::getMatrixY() const
{
	return _matrixY;
}

void Element::changeFallingState(bool newState)
{
	_isFalling = newState;
}

bool Element::GetFallingState() const
{
	return _isFalling;
}

std::uint16_t Element::getWindowX() const
{
	return _windowX;
}
std::uint16_t Element::getWindowY() const
{
	return _windowY;
}

void Element::setColor(sf::Color color)
{
	_color = color;
}

sf::Color Element::getColor() const
{
	return _color;
}

ElementType Element::getType() const
{
	return _type;
}