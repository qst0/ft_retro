#include <ncurses.h>
#include <unistd.h>

#include <iostream>

#define DELAY 30000

void draw_borders(WINDOW *screen) {
 	int x, y, i; getmaxyx(screen, y, x);
   	// 4 corners 
 	attron(COLOR_PAIR(2));
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	// sides 
 	attron(COLOR_PAIR(1));
	for (i = 1; i < (y - 1); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	} // top and bottom
	for (i = 1; i < (x - 1); i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}

void promise_colorsafe() {
 if (has_colors() == FALSE) {
  endwin();
  std::cout << "Your terminal doesn't support color!"
   << std::endl;
  std::exit(1); //No color, no game.
 }
 start_color();

 // Prepare some color pairs
 init_pair(0, COLOR_WHITE, COLOR_RED);
 init_pair(1, COLOR_RED, COLOR_WHITE);
 init_pair(2, COLOR_RED, COLOR_BLUE);
 //Set our default colors to color pair 0
 attron(COLOR_PAIR(0));
}

void init_game_env(void) {
 initscr();
 promise_colorsafe();
 noecho();
 curs_set(FALSE);
}

int main(int argc, char *argv[]) {
 (void)argc;
 (void)argv;
 //resize the terminal, works but doesn't work ???
 //Doesn't effect the vars maybe?
 //Certainly doesn't work on iterm2
 std::system("printf '\e[8;24;80t'");
 
 //Ready ncurses and the game env
 init_game_env();

 //Screen and window vars
 int parent_x, parent_y, new_x, new_y;
 int score_size = 4;

 //Setup our windows
 getmaxyx(stdscr, parent_y, parent_x);
 WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
 WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
 draw_borders(field);
 draw_borders(score);

 //Bouncing Ball vars
 int x = 42, y = 10;
 int max_x = 0;
 int max_y = 0;
 int next_x = 0;
 int x_direction = 1;
 int next_y = 0;
 int y_direction = 1;


 while(42) {
  getmaxyx(stdscr, new_y, new_x);
  if (new_y != parent_y || new_x != parent_x) { 
   parent_x = new_x;
   parent_y = new_y; 
   wresize(field, new_y - score_size, new_x);
   wresize(score, score_size, new_x);
   mvwin(score, new_y - score_size, 0);
   wclear(stdscr);
   wclear(field);
   wclear(score);
   draw_borders(field);
   draw_borders(score);
  }

  // draw to our windows
  mvwprintw(field, 1, 1, "Field");
  mvwprintw(score, 1, 1, "Score");
  // refresh each window
  wrefresh(field);
  wrefresh(score);
 
	//old ??

  //clear(); // clear all old chars
  //draw_borders(stdscr);
  getmaxyx(field, max_y, max_x);
  mvwprintw(field ,y,x, "0");
  wrefresh(field);
  //refresh();

  usleep(DELAY);

  next_x = x + x_direction;
  next_y = y + y_direction;

  if (next_x >= max_x - 1 || next_x < 1) {
   x_direction *= -1;
  } else {
   x += x_direction;
  }

  if (next_y >= max_y - 1 || next_y < 1) {
   y_direction *= -1;
  } else {
   y += y_direction;
  }

  //getch(); //wait for input?

 }

 endwin();
}

