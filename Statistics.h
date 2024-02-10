#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class Statistics : public sf::Drawable, public sf::Transformable
{
	public:
		Statistics();
		void setVerticesCount(std::uint32_t verticesCount);
		void setElementsCount(std::uint16_t elementsCount);
		void setFPS(std::float_t fps);

	private:
		std::uint32_t _verticesCount;
		std::uint16_t _elementsCount;
		std::float_t _fps;
		sf::Font _font;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

