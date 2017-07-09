#include "Player.hpp"

Player::Player() : disp_char('o') {}

Player::Player(int y, int x) : pos(y, x), disp_char('}') {}

Player::Player(int y, int x, char c) : pos(y, x), disp_char(c) {}

Player::Player(Player const & src) {
	*this = src;
}

Player & Player::operator=(Player const & rhs) {
	if (this != &rhs) {
		disp_char = rhs.disp_char;
		pos = rhs.pos;
	}
	return *this;
}

Player::~Player() {}
