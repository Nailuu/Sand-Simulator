#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>
#include <utility>
#include "Element.h"
#include "Statistics.h"

class Matrix
{
	public:
		Matrix(std::uint16_t w_height, std::uint16_t w_width, std::uint16_t elementSize);
		void swap(std::pair<std::uint16_t, std::uint16_t> target1, std::pair<std::uint16_t, std::uint16_t> target2);
		Element* getXY(std::uint16_t x, std::uint16_t y) const;
		void summonElement(std::uint16_t x, std::uint16_t y, ElementType type);
		std::uint16_t getWidth() const;
		std::uint16_t getHeight() const;
		sf::VertexArray getVertexArray() const;
		void update(Statistics* stats);

	private:
		std::uint16_t _height;
		std::uint16_t _width;
		std::uint16_t _elementSize;
		std::vector<std::vector<Element*>> _matrix;
		sf::VertexArray _vertices;
};