#include <iostream>
#include <unistd.h>

#include "Game.hpp"
#include "GameObject.hpp"

int Game::init() {
 this->win = initscr();
 cbreak();
 noecho();
 clear();
 refresh();

 keypad(win, true); //interpret action keys, not escape sequences.
 nodelay(win, true); //disable wgetch blocking.
 curs_set(0); //make cursor invisible.

 if(!has_colors()) {
  endwin();
  std::cout << "ERROR: No color, no game..." << std::endl;
  std::exit(1);
 } else { start_color(); }
 
 //TODO figure out why this doesn't work
 //if(!can_change_color()) {}
 //init_color(COLOR_RED, 0, 1000, 0);
 // Should make red into Blue...

 init_pair(1, COLOR_WHITE, COLOR_BLACK);
 wbkgd(win, COLOR_PAIR(1)); 

 attron(A_BOLD);
 box(win, 0, 0);
 attroff(A_BOLD);

 //init player (maybe it's own func?)
 p1.disp_char = '0';
 p1.pos.x = 12;
 p1.pos.y = 6;

 return (0);
}

void Game::run() {
 move (5, 5);

 std::string text = "Hello World!";
 for (size_t i = 0; i < text.size(); i++) {
  addch(text[i]);
  addch(' ');
 }

 int maxy, maxx;
 getmaxyx(win, maxy, maxx);

 Rect game_area;
 game_area.x = 0;
 game_area.y = 0;
 game_area.width = maxx;
 game_area.length = maxy;

 stars.setBounds(game_area);

 int in_char;
 while(42){
	
	 for (size_t i = 0; i < stars.getCount(); i++) {
	 if (stars.getData()[i].isActive()) {
		int star_x = stars.getData()[i].getPos().x;
		int star_y = stars.getData()[i].getPos().y;
		 mvaddch(star_y, star_x, ' ');
	 }
	}

	usleep(30000); // 30ms

	stars.update();
	
	// NEW CODE ABOVE

 	in_char = wgetch(win);

	mvaddch(p1.pos.y, p1.pos.x, ' ');

	switch(in_char) {
	 case 'q':
		 std::exit(0);
	 case KEY_UP:
	 case 'w':
		 p1.pos.y -= 1;
		 break;
	 case KEY_DOWN:
	 case 's':
		 p1.pos.y += 1;
		 break;
	 case KEY_LEFT:
	 case 'a':
		 p1.pos.x -= 1;
		 break;
	 case KEY_RIGHT:
	 case 'd':
		 p1.pos.x += 1;
		 break;
	 default:
		 break;
	}

	mvaddch(p1.pos.y, p1.pos.x, p1.disp_char);

	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			int star_x = stars.getData()[i].getPos().x;
			int star_y = stars.getData()[i].getPos().y;
			mvaddch(star_y, star_x, '*');
		}
	}

	usleep(10000); // 10ms
	
	refresh();
 }
}

void Game::close() {
 endwin();
}
