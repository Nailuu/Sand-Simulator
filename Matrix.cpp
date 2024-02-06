#include "Matrix.h"
#include "Sand.h"
#include <iostream>
#include <algorithm>

Matrix::Matrix(std::uint16_t w_height, std::uint16_t w_width, std::uint16_t elementSize)
{
	_elementSize = elementSize;
	_height = w_height / _elementSize;
	_width = w_width / _elementSize;

	_max_x = _width - _elementSize;
	_max_y = _height - _elementSize;

	_vertices = sf::VertexArray();

	_matrix = std::vector<std::vector<Element*>>(_width, std::vector<Element*>());

	for (auto& element : _matrix)
	{
		element.resize(_height);
	}
}

// pair.first = x, pair.second = y
void Matrix::swap(std::pair<std::uint16_t, std::uint16_t> target1, std::pair<std::uint16_t, std::uint16_t> target2)
{
	std::swap(_matrix[target1.first][target1.second], _matrix[target2.first][target2.second]);
}

Element* Matrix::getXY(std::uint16_t x, std::uint16_t y) const
{
	return _matrix[x][y];
}

std::uint16_t Matrix::getMaxX() const
{
	return _max_x;
}

std::uint16_t Matrix::getMaxY() const
{
	return _max_y;
}

void Matrix::update()
{
	std::uint16_t x = 0;

	for (auto i = _matrix.rbegin(); i != _matrix.rend(); i++)
	{
		for (auto j = _matrix[x].rbegin(); j != _matrix[x].rend(); j++)
		{
			if (*j != nullptr)
				(*j)->update(*this);
		}
		x++;
	}
}

void Matrix::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& element : _matrix)
	{
		for (auto& element2 : element)
		{
			if (element2 != nullptr)
			{
				sf::RectangleShape rect = sf::RectangleShape();

				rect.setSize(sf::Vector2f(_elementSize, _elementSize));
				rect.setFillColor(sf::Color::Yellow);
				rect.setPosition(element2->getMatrixX() * _elementSize, element2->getMatrixY() * _elementSize);

				target.draw(rect);
			}
		}
	}
}

void Matrix::summonElement(std::uint16_t x, std::uint16_t y, ElementType type)
{
	switch (type)
	{
		case SAND:
			Sand *element = new Sand(x, y, type, _elementSize);
			_matrix[element->getMatrixX()][element->getMatrixY()] = element;
	}
}