#include "Bullets.hpp"
#include <ncurses.h>
#include <string>

void	Bullets::update() {
	//Update all active objects
	// addstr("enter bullet update");
	for (size_t i = 0; i < object_count; i++) {
		if (object_set[i].isActive()) {
			if (object_set[i].getPos().x == field_bounds.width - 2) // if it reaches the right end
				object_set[i].deactivate();
			object_set[i].updateToRight();
		}
	}
}

void	Bullets::activate(int p_x, int p_y) {
	//Find an inactive object, activate it.
	// addstr("bullet active");
	size_t i;

	i = 0;
	while (i < object_count) {
		if (!object_set[i].isActive())
			break;
		i++;
	}
	object_set[i].activate(p_x + 1, p_y);
	// addstr("bullet active ");
}
