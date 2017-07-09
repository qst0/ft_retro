#include "Rect.hpp"

Rect::Rect() : y(0), x(0), height(0), width(0) {}

Rect::Rect(int height, int width) : y(0), x(0), height(height), width(width) {}

Rect::Rect(int y, int x, int height, int width)
	: y(y), x(x), height(height), width(width) {}

Rect::Rect(Rect const & src) {
	*this = src;
}

Rect & Rect::operator=(Rect const & rhs) {
	if (this != &rhs) {
		this->y = rhs.y;
		this->x = rhs.x;
		this->height = rhs.height;
		this->width = rhs.width;
	}
	return *this;
}

Rect::~Rect() {}
