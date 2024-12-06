#pragma once
#include "Figure.h"

class Box : public Figure
{
public:
	explicit Box(int size, int offsetX, int offsetY);

	void draw() override;
	bool isInnerPoint(int x, int y) override;
};

