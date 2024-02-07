#include "Sand.h"
#include <iostream>

Sand::Sand(std::uint16_t x, std::uint16_t y, ElementType type, std::uint16_t elementSize) : Element(x, y, type, elementSize)
{

}

void Sand::update(Matrix *matrix)
{
	if (getMatrixY() == (*matrix).getHeight() - 1) return;

	else if ((*matrix).getXY(getMatrixX(), getMatrixY() + 1) == nullptr)
	{
		(*matrix).swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX(), getMatrixY() + 1));
		set(getMatrixX(), getMatrixY() + 1);
		return;
	}

	else if (getMatrixX() != ((*matrix).getWidth() - 1) && (*matrix).getXY(getMatrixX() + 1, getMatrixY() + 1) == nullptr)
	{
		(*matrix).swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() + 1, getMatrixY() + 1));
		set(getMatrixX() + 1, getMatrixY() + 1);
		return;
	}

	else if (getMatrixX() != 0 && (*matrix).getXY(getMatrixX() - 1, getMatrixY() + 1) == nullptr)
	{
		(*matrix).swap(std::make_pair(getMatrixX(), getMatrixY()), std::make_pair(getMatrixX() - 1, getMatrixY() + 1));
		set(getMatrixX() - 1, getMatrixY() + 1);
		return;
	}

	else
		changeFallingState(false);
}