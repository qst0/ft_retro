#include "Game.hpp"
#include "GameObjectField.hpp"

Game::Game( void ) : win(initscr()), p1(6, 12) {  // init() and init player 1 
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
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, 7, 8);
	wbkgd(win, COLOR_PAIR(1)); 

	attron(A_BOLD);
	attron(COLOR_PAIR(3));
	box(win, 0, 0);
	attroff(COLOR_PAIR(3));
	attroff(A_BOLD);
}

Game::Game( Game const & src ) {
	*this = src;
}

Game & Game::operator=( Game const & rhs ) {
	if ( this != &rhs ) {
		this->win = rhs.win;
	}
	return *this;
}

Game::~Game( void ) {  // close()
	endwin();
}

/* ******************************* ACTION  ******************************* */

bool	Game::collisionHandler() {
	int star_x, star_y;
	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			star_x = stars.getData()[i].getPos().x;
			star_y = stars.getData()[i].getPos().y;
			if (star_x == p1.pos.x && star_y == p1.pos.y) {
				return true;
			}
		}
	}
	return false;
}

void	Game::gameOver() {
	int in_char;

	in_char = wgetch(win);
	attron(A_BOLD);
	wbkgd(win, COLOR_PAIR(2));
	mvaddch(p1.pos.y, p1.pos.x, 'X');
	while(42) {
		in_char = wgetch(win);
		if (in_char == 'q') {
			clear();
			endwin();
			std::exit(0);
		}
		if (in_char == 'r') {
			attroff(A_BOLD);
			wbkgd(win, COLOR_PAIR(1));
			break;
		}
		move (11, 32);
		std::string text = "GAME OVER";
		for (size_t i = 0; i < text.size(); i++) {
		  addch(text[i]);
		  addch(' ');
		  usleep(30000);
		  refresh();
		}
		move (12, 24);
		text = "Press `q` to quit...";
		for (size_t i = 0; i < text.size(); i++) {
		  addch(text[i]);
		  addch(' ');
		  usleep(30000);
		  refresh();
		}
	}
}

void	Game::run() {

	int maxy, maxx;
	int star_x, star_y;
	getmaxyx(win, maxy, maxx);
	Rect game_area(maxy, maxx); // init rect with 0,0 origin and width and height
	stars.setBounds(game_area);

	int in_char;
	while(42){
 
 	// Collision detection here
	if (collisionHandler() == true)
		gameOver();

	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			star_x = stars.getData()[i].getPos().x;
			star_y = stars.getData()[i].getPos().y;
			mvaddch(star_y, star_x, ' ');
		}
	}

	usleep(30000); // 30ms

	stars.update();
	
	// NEW CODE ABOVE

	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			star_x = stars.getData()[i].getPos().x;
			star_y = stars.getData()[i].getPos().y;
			mvaddch(star_y, star_x, '*');
		}
	}

 	in_char = wgetch(win);

	mvaddch(p1.pos.y, p1.pos.x, ' ');

	if (in_char == 'q' || in_char == 27)
	{
		endwin();
		std::exit(0);
	}
	else if ((in_char == KEY_UP || in_char == 'w') && p1.pos.y > 1)
		p1.pos.y--;
	else if ((in_char == KEY_DOWN || in_char == 's') && p1.pos.y < maxy - 2)
		p1.pos.y++;
	else if ((in_char == KEY_LEFT || in_char == 'a') && p1.pos.x > 1)
		p1.pos.x--;
	else if ((in_char == KEY_RIGHT || in_char == 'd') && p1.pos.x < maxx - 2)
		p1.pos.x++;
	
	mvaddch(p1.pos.y, p1.pos.x, p1.disp_char);

	usleep(10000); // 10ms
	
	refresh();
	}
}

// void Game::close() {
//  endwin();
// }
