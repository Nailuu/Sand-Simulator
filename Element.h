#pragma once

#include <SFML/Graphics.hpp>
#include "ElementType.h"
#include <cstdint>
#include <array>

class Matrix;

class Element
{
	public:
		Element(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize);
		void virtual update(Matrix *matrix) = 0;
		std::uint16_t getMatrixX() const;
		std::uint16_t getMatrixY() const;
		std::uint16_t getWindowX() const;
		std::uint16_t getWindowY() const;
		bool GetFallingState() const;
		sf::Color getColor() const;
		ElementType getType() const;
		void set(std::uint16_t x, std::uint16_t y, std::uint16_t m_height);

	protected:
		void changeFallingState(bool newState);
		void setColor(sf::Color color);

	private:
		std::uint16_t _matrixX;
		std::uint16_t _matrixY;
		std::uint16_t _windowX;
		std::uint16_t _windowY;
		sf::Vector2u _velocity;
		ElementType _type;
		std::uint16_t _elementSize;
		std::array<sf::Color, 3> _colorsVariant;
		sf::Color _color;
		bool _isFalling;
};

