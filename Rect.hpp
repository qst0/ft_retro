#ifndef RECT_H
# define RECT_H

struct Rect {
	int y;
	int x;
	int height; // max Y
	int width;  // max X

	Rect(); // sets all to 0
	Rect(int height, int width); // sets y and x to 0
	Rect(int y, int x, int height, int width); // can have a different origin point
	Rect(Rect const & src);
	Rect & operator=(Rect const & rhs);
	~Rect();
};

#endif
