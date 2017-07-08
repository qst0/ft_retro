#include <iostream> //cout cin lol
#include <unistd.h> //sleep

#include <ncurses.h> //all teh biz

int main(void) {
 int ch;
 
 initscr(); //Gotta do this first
 noecho(); //supress the automatic repeats
 keypad(stdscr, TRUE); // When you want special keys
 curs_set(FALSE); // ??? Learn about it.
 WINDOW * win = newwin(10, 10, 3, 3);
 wmove(win, 3, 3); // moves the cursor
 nodelay(stdscr, TRUE);
 for (;;) {
  if ((ch = getch()) == ERR) {
   /* user hasn't responded */
  } else {
   /* user has pressed a key ch */
	  std::cout << ch << " Oh wow!" << std::endl;
  }
 }
 sleep(1);
 wrefresh(win); //if you make a change, refresh!
 refresh(); // just like wrefresh(stdscr)
 endwin(); // Puts the terminal back out of window mode
}
