#include <iostream> //arc4random

#include "GameObject.hpp"

GameObject::GameObject() : pos(-42, -42) {
	// pos.x = -42;
	// pos.y = -42;
	active = false;
}

GameObject::GameObject(GameObject const & src) {
	*this = src;
}

GameObject & GameObject::operator=(GameObject const & rhs) {
	if(this != &rhs) {
		this->pos = rhs.getPos();
		this->active = rhs.isActive();
	}
	return *this;
}

/* ******************************* ACTION  ******************************* */

void GameObject::update() {
	pos.y += 1;
}

void GameObject::activate(int nx, int ny) { // should set y val to -1 ??
	pos.x = nx;
	pos.y = ny;
	active = true;
}

void GameObject::deactivate() {
	active = false;
}

/* ******************************* GETTERS  ******************************* */

bool GameObject::isActive() const {
	return active;
}

Vec2i GameObject::getPos() const {
	return pos;
}
