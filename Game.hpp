#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>

# include "GameObjectField.hpp" // contains GameObject.hpp and Rect.hpp and Player.hpp

class Game {

public: 
	Game();
	Game(Game const & src);
	Game & operator=(Game const & rhs);
	~Game();

	WINDOW*					win;
	Player					p1;
	GameObjectField	stars;

	int							init();
	void						run();
	void						close();

private:

};

#endif
