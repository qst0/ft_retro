#ifndef GAMEOBJECTFIELD_H
# define GAMEOBJECTFIELD_H

# include "GameObject.hpp"
# include "Rect.hpp"

#include <iostream>
#include <unistd.h>

class GameObjectField {

public:
	GameObjectField();
	GameObjectField(GameObjectField const & src);
	GameObjectField & operator=(GameObjectField const & rhs);
	~GameObjectField();

	void				update();
	void				setBounds(Rect r);

	GameObject*	getData() const;
	size_t			getCount() const;
	Rect				getFieldBounds() const;

private:
	Rect				field_bounds;
	GameObject*	object_set;
	size_t			object_count;
};

#endif