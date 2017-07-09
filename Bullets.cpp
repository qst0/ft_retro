#include "Bullets.hpp"
#include <ncurses.h>
#include <string>

void	Bullets::update() {
	for (size_t i = 0; i < object_count; i++) {
		if (object_set[i].isActive()) {
		   	// if it reaches the right end
			if (object_set[i].getPos().x == field_bounds.width - 2)
				object_set[i].deactivate();
			object_set[i].updateToRight();
		}
	}
}

void	Bullets::activate(int p_x, int p_y) {
	size_t i;

	i = 0;
	while (i < object_count) {
		if (!object_set[i].isActive())
			break;
		i++;
	}
	object_set[i].activate(p_x, p_y);
}
