#include <ncurses.h>
#include <string>

#include "Bullets.hpp"

void	Bullets::update() {
	for (size_t i = 0; i < object_count; i++) {
		if (object_set[i].isActive()) {
		   	// deactivate if out of bounds
			if (object_set[i].getPos().x == field_bounds.width - 2)
				object_set[i].deactivate();
			object_set[i].updateToRight();
		}
	}
}

void	Bullets::activate(int p_x, int p_y) {	
	for (size_t i = 0; i < object_count; i++) {
		if (!object_set[i].isActive()) {
			object_set[i].activate(p_x, p_y);
			break;
		}
	}
	system("afplay -t 20 ./mp3/pew.mp3 &");
}
