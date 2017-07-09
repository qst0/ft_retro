#ifndef BULLETS_H
# define BULLETS_H

#include "GameObjectField.hpp"

class Bullets : public GameObjectField {

public:
	void	update();
	void	activate(int p_x, int p_y);
};

#endif
