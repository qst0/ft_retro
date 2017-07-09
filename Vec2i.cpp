#include "Vec2i.hpp"

Vec2i::Vec2i() : y(0), x(0) {}

Vec2i::Vec2i(int y, int x) : y(y), x(x) {}

Vec2i::Vec2i(Vec2i const & src) {
	*this = src;
}

Vec2i & Vec2i::operator=(Vec2i const & rhs) {
	if (this != &rhs) {
		y = rhs.y;
		x = rhs.x;
	}
	return *this;
}

Vec2i::~Vec2i() {}
