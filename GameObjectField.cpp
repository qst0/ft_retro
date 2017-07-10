#include "GameObjectField.hpp"

GameObjectField::GameObjectField() {
	object_count = 42;
	object_set = new GameObject[object_count];

	//We can set objects,
	// but our loop auto creates some anyway.
	//object_set[0].activate(4,4);
	//object_set[1].activate(3,3);
}

GameObjectField::GameObjectField(GameObjectField const & src) {
	*this = src;
}

GameObjectField & GameObjectField::operator=(GameObjectField const & rhs) {
	if(this != &rhs) {
		this->field_bounds = rhs.getFieldBounds();
		this->object_set = rhs.getData();
		this->object_count = rhs.getCount();
	}
	return *this;
}

GameObjectField::~GameObjectField() {
	delete [] object_set;
}

/* ******************************* ACTION  ******************************* */

size_t GameObjectField::update() {
	size_t score_mod = 0;
	//Update all active objects
	for (size_t i = 0; i < object_count; i++) {
	 if (object_set[i].isActive()) {
		 // + 2 for boarder
		 if (object_set[i].getPos().x < field_bounds.x + 2) {
			 object_set[i].deactivate();
			 score_mod++;
		 } else {
		 object_set[i].updateToLeft();
		 }
	 }
	}

	//Find inactive objects, activate them.
	if (arc4random() % 2 == 1) // wave sparcity
	{
		for (size_t i = 0; i < object_count; i++) {
			if (!object_set[i].isActive()) {
				if (arc4random() % 10 == 1) { // unit sparcity

					// Why doesn't one laser destroy an `@` ?
					//OBJECTS CAN SPAWN ONTOP OF OTHER OBJECTS!
					
					// Spawn at the far right
					object_set[i].activate(
					 (field_bounds.width - 2),
					 (arc4random() % (field_bounds.height - 2)) + 1);

					// Spawn at the top
					//object_set[i].activate(
					// arc4random() % (field_bounds.width - 2) + 1, 1);
				}
			}
		} //If we don't have inactive objects, so be it...
	}

	return score_mod;
}

void GameObjectField::setBounds(Rect r) {
	field_bounds = r;
}

/* ******************************* GETTERS  ******************************* */


//Reworked to avoid vector
size_t GameObjectField::getCount() const {
	return object_count;
}

GameObject* GameObjectField::getData() const {
	return object_set;
}

Rect GameObjectField::getFieldBounds() const {
	return field_bounds;
}
