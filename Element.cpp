#include "Element.h"

Element::Element(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize)
{
	_elementSize = elementSize;
	_matrixX = (x - (x % _elementSize)) / _elementSize;
	_matrixY = (y - (y % _elementSize)) / _elementSize;
	_type = type;
}

void Element::set(std::uint16_t x, std::uint16_t y)
{
	_matrixX = x;
	_matrixY = y;
}

std::uint16_t Element::getMatrixX() const
{
	return _matrixX;
}

std::uint16_t Element::getMatrixY() const
{
	return _matrixY;
}