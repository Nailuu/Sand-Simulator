#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>
#include <utility>
#include "Element.h"

class Matrix : public sf::Drawable
{
	public:
		Matrix(std::uint16_t w_height, std::uint16_t w_width, std::uint16_t elementSize);
		void swap(std::pair<std::uint16_t, std::uint16_t> target1, std::pair<std::uint16_t, std::uint16_t> target2);
		Element* getXY(std::uint16_t x, std::uint16_t y) const;
		void update();
		void summonElement(std::uint16_t x, std::uint16_t y, ElementType type);
		std::uint16_t getMaxX() const;
		std::uint16_t getMaxY() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		std::uint16_t _height;
		std::uint16_t _width;
		std::uint16_t _max_x;
		std::uint16_t _max_y;
		std::uint16_t _elementSize;
		std::vector<std::vector<Element*>> _matrix;
		sf::VertexArray _vertices;
};