#include "Rect.h"

Rect::Rect(unsigned int width, unsigned int height)
{
	this->size = Size(width, height);
}

Rect::Rect(Point point, Size size)
{
	this->point = point;
	this->size = size;
}

Rect::Rect(int x, int y, unsigned int width, unsigned int height)
{
	this->point = Point(x, y);
	this->size = Size(width, height);
}

int Rect::minX() const
{
	return point.x;
}

int Rect::maxX() const
{
	return point.x + size.width;
}

int Rect::minY() const
{
	return point.y;
}

int Rect::maxY() const
{
	return point.y + size.height;
}
