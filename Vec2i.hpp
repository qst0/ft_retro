#ifndef VEC2I_H
# define VEC2I_H

struct Vec2i {
	int	y;
	int	x;

	Vec2i();
	Vec2i(int y, int x);
	Vec2i(Vec2i const & src);
	Vec2i & operator=(Vec2i const & rhs);
	~Vec2i();
};

#endif