#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>

typedef struct {
	int x;
	int y;
} vec2i;

typedef struct {
	unsigned int x;
	unsigned int y;
} vec2ui;

typedef struct {
	vec2i pos;
	char disp_char;
} player;

class Game {

public: 
	
 WINDOW* win;
 player p1;

 int init();
 void run();
 void close();

private:

};

#endif
