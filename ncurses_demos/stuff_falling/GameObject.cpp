#include <iostream> //arc4random

#include "GameObject.hpp"

GameObject::GameObject() {
	pos.x = -42;
	pos.y = -42;
	active = false;
}

void GameObject::update() {
	pos.y += 1;
}

void GameObject::activate(int nx, int ny) {
	pos.x = nx;
	pos.y = ny;
	active = true;
}

void GameObject::deactivate() {
	active = false;
}

bool GameObject::isActive() {
	return active;
}

vec2i GameObject::getPos() const {
	return pos;
}

void GameObjectField::setBounds(Rect r) {
	field_bounds = r;
}

// GAME OBJECT FIELD

GameObjectField::GameObjectField() {
	object_count = 42;
	object_set = new GameObject[object_count];

	//We can set objects,
	// but our loop auto creates some anyway.
	//object_set[0].activate(4,4);
	//object_set[1].activate(3,3);
}

GameObjectField::~GameObjectField() {
	delete [] object_set;
}

//Reworked to avoid vector
size_t GameObjectField::getCount() const {
	return object_count;
}

GameObject* GameObjectField::getData() const {
	return object_set;
}

void GameObjectField::update() {
	//Update all active objects
	for (size_t i = 0; i < object_count; i++) {
	 if (object_set[i].isActive()) {
		 if (object_set[i].getPos().y > field_bounds.y
				+ field_bounds.length)
			 object_set[i].deactivate();
		 object_set[i].update();
	 }
	}

	//Find an inactive object, activate it.
	if (arc4random() % 10 == 1) // wave sparcity
	{
		for (size_t i = 0; i < object_count; i++) {
			if (!object_set[i].isActive()) {
				if (arc4random() % 10 == 1) { // unit sparcity
					object_set[i].activate(arc4random() % field_bounds.width, 0);
				}
			}
		} //If we don't have an inactive object, so be it...
	}
}
