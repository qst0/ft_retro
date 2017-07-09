#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>

# include "GameObject.hpp" 

class Game {

public: 
	
 WINDOW* win;
 player p1;
 GameObjectField stars;

 int init();
 void run();
 void close();

private:

};

#endif
