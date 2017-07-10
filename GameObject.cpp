#include <iostream> //arc4random
#include <ncurses.h>
#include "GameObject.hpp"

GameObject::GameObject() : pos(-42, -42), active(false) {}

GameObject::GameObject(GameObject const & src) { *this = src; }

GameObject & GameObject::operator=(GameObject const & rhs) {
	if (this != &rhs) {
		this->pos = rhs.getPos();
		this->active = rhs.isActive();
	}
	return *this;
}

GameObject::~GameObject() {}

/* ******************************* ACTION  ******************************* */

void GameObject::updateToLeft() {
	pos.x -= 1;
}

void GameObject::updateToRight() {
	pos.x += 1;
}

//toggle active to true and move pos to nx ny
void GameObject::activate(int nx, int ny) { // should set y val to -1 ??
	mvaddch(pos.y, pos.x, ' ');
	pos.x = nx;
	pos.y = ny;
	active = true;
}

//toggle active to false and move pos off screen
void GameObject::deactivate() {
	mvaddch(pos.y, pos.x, ' ');
	pos.x = -42;
	pos.y = -42;
	active = false;
}

/* ******************************* GETTERS  ******************************* */

bool GameObject::isActive() const {
	return active;
}

Vec2i GameObject::getPos() const {
	return pos;
}
