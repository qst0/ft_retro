#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>

# include "GameObjectField.hpp" // contains GameObject.hpp and Rect.hpp and Player.hpp

class Game {

public:
	WINDOW*					win;
	Player					p1;
	GameObjectField	stars;

	Game();
	Game(Game const & src);
	Game & operator=(Game const & rhs);
	~Game();

	void						run();
	bool						collisionHandler();	// returns true if collision is detected?
	void						gameOver(); // if collision detected puts Game Over screen

private:

};

#endif
