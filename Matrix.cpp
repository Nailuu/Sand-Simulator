#include "Matrix.h"
#include "Sand.h"
#include "Water.h"
#include "Stone.h"
#include "Statistics.h"
#include <iostream>
#include <algorithm>

Matrix::Matrix(std::uint16_t w_height, std::uint16_t w_width, std::uint16_t elementSize)
{
	_elementSize = elementSize;
	_height = w_height / _elementSize;
	_width = w_width / _elementSize;

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
	if (_matrix[target1.first][target1.second] != nullptr)
		_matrix[target1.first][target1.second]->set(target2.first, target2.second, _height);

	if (_matrix[target2.first][target2.second] != nullptr)
		_matrix[target2.first][target2.second]->set(target1.first, target1.second, _height);
		
	std::swap(_matrix[target1.first][target1.second], _matrix[target2.first][target2.second]);
}

Element* Matrix::getXY(std::uint16_t x, std::uint16_t y) const
{
	if (x >= _width || y >= _height)
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

void Matrix::update(Statistics* stats)
{
	std::uint16_t x = 0;
	std::uint32_t verticesCount = 0;

	_vertices = sf::VertexArray(sf::Triangles, 0);

	for (auto i = _matrix.rbegin(); i != _matrix.rend(); i++)
	{
		for (auto j = _matrix[x].rbegin(); j != _matrix[x].rend(); j++)
		{
			if (*j != nullptr)
			{
				Element* ptr = *j;
				sf::Color elementColor = ptr->getColor();

				if ((*j)->GetFallingState())
					(*j)->update(this);

				// Render "pixel" element as 2 triangles to form a square
				verticesCount += 6;
				_vertices.resize(verticesCount);
				_vertices[verticesCount - 6].position = sf::Vector2f(ptr->getWindowX(), ptr->getWindowY() + 5);
				_vertices[verticesCount - 6].color = elementColor;
				_vertices[verticesCount - 5].position = sf::Vector2f(ptr->getWindowX(), ptr->getWindowY());
				_vertices[verticesCount - 5].color = elementColor;
				_vertices[verticesCount - 4].position = sf::Vector2f(ptr->getWindowX() + 5, ptr->getWindowY());
				_vertices[verticesCount - 4].color = elementColor;

				_vertices[verticesCount - 3].position = sf::Vector2f(ptr->getWindowX() + 5, ptr->getWindowY());
				_vertices[verticesCount - 3].color = elementColor;
				_vertices[verticesCount - 2].position = sf::Vector2f(ptr->getWindowX() + 5, ptr->getWindowY() + 5);
				_vertices[verticesCount - 2].color = elementColor;
				_vertices[verticesCount - 1].position = sf::Vector2f(ptr->getWindowX(), ptr->getWindowY() + 5);
				_vertices[verticesCount - 1].color = elementColor;
			}
		}
		x++;
	}

	stats->setVerticesCount(verticesCount);
	stats->setElementsCount(verticesCount / 6);
}

void Matrix::summonElement(std::uint16_t x, std::uint16_t y, ElementType type)
{
	std::uint16_t matrixX = (x - (x % _elementSize)) / _elementSize;
	std::uint16_t matrixY = (y - (y % _elementSize)) / _elementSize;

	if (matrixX >= getWidth() || matrixY >= getHeight())
		return;

	// avoid creating multiple object on the same x y and creating mem leaks
	if (_matrix[matrixX][matrixY] == nullptr)
	{
		switch (type)
		{
			case SAND:
			{
				Element* sand = new Sand(x, y, type, _elementSize);
				_matrix[sand->getMatrixX()][sand->getMatrixY()] = sand;
				break;
			}

			case WATER:
			{
				Element* water = new Water(x, y, type, _elementSize);
				_matrix[water->getMatrixX()][water->getMatrixY()] = water;
				break;
			}

			case STONE:
				Element* stone = new Stone(x, y, type, _elementSize);
				_matrix[stone->getMatrixX()][stone->getMatrixY()] = stone;
				break;
		}
	}
}

sf::VertexArray Matrix::getVertexArray() const
{
	return _vertices;
}