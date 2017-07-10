#include "Game.hpp"

int main(int argc, char** argv) {
 (void)argc;
 (void)argv;
 int run;
 Game *game = new Game;

 game->init();
 run = game->run();
 while (run == 1) {
 	delete game;
 	game = new Game();
 	run = game->run();
 }
 delete game;
 return (0);
}
