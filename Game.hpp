#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>

// # include "GameObjectField.hpp" // contains GameObject.hpp and Rect.hpp and Player.hpp
# include "Bullets.hpp"
# include "Player.hpp"

class Game {

public:
	WINDOW*					win;
	Player					p1;
	GameObjectField	stars;
	Bullets					bullet;

	Game();
	Game(Game const & src);
	Game & operator=(Game const & rhs);
	~Game();

	void						run();
	bool						collisionHandler();	// returns true if collision is detected?
	void						shootStar();
	void						trailCleaner();
	void						print();
	void						controlHandler(int maxx, int maxy);
	void						gameOver(); // if collision detected puts Game Over screen

private:

};

#endif
