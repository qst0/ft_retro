#include "Vec2ui.hpp"

Vec2ui::Vec2ui() : y(0), x(0) {}

Vec2ui::Vec2ui(unsigned int y, unsigned int x) : y(y), x(x) {}

Vec2ui::Vec2ui(Vec2ui const & src) {
	*this = src;
}

Vec2ui & Vec2ui::operator=(Vec2ui const & rhs) {
	if (this != &rhs) {
		y = rhs.y;
		x = rhs.x;
	}
	return *this;
}

Vec2ui::~Vec2ui() {}
