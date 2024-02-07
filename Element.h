#pragma once

#include <SFML/Graphics.hpp>
#include "ElementType.h"
#include <cstdint>

class Matrix;

class Element
{
	public:
		Element(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize);
		void virtual update(Matrix *matrix) = 0;
		std::uint16_t getMatrixX() const;
		std::uint16_t getMatrixY() const;
		bool GetFallingState() const;

	protected:
		void set(std::uint16_t x, std::uint16_t y);
		void changeFallingState(bool newState);

	private:
		std::uint16_t _matrixX;
		std::uint16_t _matrixY;
		sf::Vector2u _velocity;
		ElementType _type;
		std::uint16_t _elementSize;
		bool _isFalling;
};

