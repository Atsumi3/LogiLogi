#pragma once
#include "Point.h"
#include "Size.h"

// ���W�ƃT�C�Y
class Rect
{
public:
	Point point;
	Size size;

	Rect() {};

	Rect(Point point, Size size);

	Rect(unsigned int width, unsigned int height);
	Rect(int x, int y, unsigned int width, unsigned int height);

	int minX() const;
	int maxX() const;
	int minY() const;
	int maxY() const;
};