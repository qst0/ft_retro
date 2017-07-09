#ifndef PLAYER_H
# define PLAYER_H

#include "Vec2i.hpp"

struct Player {
	Vec2i	pos;
	char	disp_char;

	Player();
	Player(int y, int x);
	Player(int y, int x, char c);
	Player(Player const & src);
	Player & operator=(Player const & rhs);
	~Player();
};

#endif
