#ifndef VEC2UI_H
# define VEC2UI_H

struct Vec2ui {
	unsigned int	y;
	unsigned int	x;

	Vec2ui();
	Vec2ui(unsigned int y, unsigned int x);
	Vec2ui(Vec2ui const & src);
	Vec2ui & operator=(Vec2ui const & rhs);
	~Vec2ui();
};

#endif
