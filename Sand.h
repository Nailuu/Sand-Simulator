#pragma once

#include "Element.h"
#include "Matrix.h"
#include <cstdint>

class Sand : public Element
{
	public:
		Sand(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize);
		void update(Matrix matrix) override;
};

