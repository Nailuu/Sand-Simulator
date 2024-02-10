#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <cstdint>
#include "ElementType.h"

class Selector : public sf::Drawable, public sf::Transformable
{
	public:
		Selector(std::uint16_t w_width, std::uint16_t w_height);
		ElementType getSelectedElement() const;
		void changeSelection(std::int16_t direction);

	private:
		std::vector<std::pair<ElementType, sf::Texture>> _elements;
		std::int16_t _selectedElement;
		sf::Font _font;
		std::uint16_t _windowWidth;
		std::uint16_t _windowHeight;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};