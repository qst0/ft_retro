#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>
# include <ctime>

// # include "GameObjectField.hpp" // contains GameObject.hpp and Rect.hpp and Player.hpp
# include "Bullets.hpp"
# include "Player.hpp" // has GameObjectField.hpp

class Game {

public:
	
	WINDOW*						main_window;
	WINDOW*						game_window;

	size_t						tick;
	size_t						score;
	std::time_t				start;

	Player						p1;
	GameObjectField		stars;
	GameObjectField		dust;
	Bullets						bullets;

	Game();
	Game(Game const & src);
	Game & operator=(Game const & rhs);
	~Game();

	int							run();
	void						init();
	bool						collisionHandler();	// returns true if collision is detected?
	void						shootStar();
	void						trailCleaner();
	void						print();
	void						controlHandler(int maxx, int maxy);
	int							gameOver(); // if collision detected puts Game Over screen

private:

};

#endif
