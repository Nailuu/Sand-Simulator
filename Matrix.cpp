#include "Matrix.h"
#include "Sand.h"
#include <iostream>
#include <algorithm>

Matrix::Matrix(std::uint16_t w_height, std::uint16_t w_width, std::uint16_t elementSize)
{
	_elementSize = elementSize;
	_height = w_height / _elementSize;
	_width = w_width / _elementSize;

	//_vertices = sf::VertexArray();

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
	if (x >= _width - 1 || y >= _height - 1)
		return nullptr;
	return _matrix[x][y];
}

std::uint16_t Matrix::getWidth() const
{
	return _width;
}

std::uint16_t Matrix::getHeight() const
{
	return _height;
}

void Matrix::update()
{
	std::uint16_t x = 0;

	for (auto i = _matrix.rbegin(); i != _matrix.rend(); i++)
	{
		for (auto j = _matrix[x].rbegin(); j != _matrix[x].rend(); j++)
		{
			if (*j != nullptr)
				(*j)->update(this);
		}
		x++;
	}
}

void Matrix::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::uint16_t x = 0;

	for (auto i = _matrix.rbegin(); i != _matrix.rend(); i++)
	{
		for (auto j = _matrix[x].rbegin(); j != _matrix[x].rend(); j++)
		{
			if (*j != nullptr)
			{
				sf::RectangleShape rect = sf::RectangleShape();

				rect.setSize(sf::Vector2f(_elementSize, _elementSize));
				rect.setFillColor(sf::Color::Yellow);
				rect.setPosition((*j)->getMatrixX() * _elementSize, (*j)->getMatrixY() * _elementSize);

				target.draw(rect);
			}
		}
		x++;
	}
}

void Matrix::summonElement(std::uint16_t x, std::uint16_t y, ElementType type)
{
	std::uint16_t matrixX = (x - (x % _elementSize)) / _elementSize;
	std::uint16_t matrixY = (y - (y % _elementSize)) / _elementSize;

	// avoid creating multiple object on the same x y and creating mem leaks
	if (_matrix[matrixX][matrixY] == nullptr)
	{
		switch (type)
		{
			case SAND:
				Element* sand = new Sand(x, y, type, _elementSize);
				_matrix[sand->getMatrixX()][sand->getMatrixY()] = sand;
		}
	}
}