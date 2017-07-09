#include <iostream>
#include <string>
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char** argv) {
 (void)argc;
 (void)argv;

 initscr();
 cbreak();
 noecho();
 clear();
 refresh();

 move(5, 5);

 std::string text = "Neo, the matrix has you...";
 for (size_t i = 0; i < text.size(); i++) {
  addch(text[i]);
  addch(' ');
  usleep(420000);
 refresh();
 }
 
 refresh();

 while(42);

 return (0);
}
