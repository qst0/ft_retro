#include "Game.hpp"
#include "GameObjectField.hpp"

Game::Game( void ) : main_window(initscr()), p1(6, 12) {  // init() and init player 1 
	cbreak();
	noecho();
	clear();
	refresh();

	keypad(main_window, true); //interpret action keys, not escape sequences.
	nodelay(main_window, true); //disable wgetch blocking.
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
	wbkgd(main_window, COLOR_PAIR(1)); 

	attron(A_BOLD);
	attron(COLOR_PAIR(3));
	box(main_window, 0, 0);
	attroff(COLOR_PAIR(3));
	attroff(A_BOLD);
}

Game::Game( Game const & src ) {
	*this = src;
}

Game & Game::operator=( Game const & rhs ) {
	if ( this != &rhs ) {
		this->main_window = rhs.main_window;
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

void	Game::shootStar() {
	int star_x, star_y;
	int	bull_x, bull_y;
	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			star_x = stars.getData()[i].getPos().x;
			star_y = stars.getData()[i].getPos().y;
			for (size_t j = 0; j < bullet.getCount(); j++) {
				bull_x = bullet.getData()[j].getPos().x;
				bull_y = bullet.getData()[j].getPos().y;
				if (star_x == bull_x && star_y == bull_y) {
					stars.getData()[i].deactivate();
					bullet.getData()[j].deactivate();
					// return true;
				}
			}
		}
	}
	// return false;
}

void	Game::gameOver() {
	int in_char;

	in_char = wgetch(main_window);
	attron(A_BOLD);
	wbkgd(main_window, COLOR_PAIR(2));
	mvaddch(p1.pos.y, p1.pos.x, 'X');
	while(42) {
		in_char = wgetch(main_window);
		if (in_char == 'q') {
			clear();
			endwin();
			std::exit(0);
		}
		if (in_char == 'r') {
			attroff(A_BOLD);
			wbkgd(main_window, COLOR_PAIR(1));
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

void	Game::trailCleaner() {
	int star_x, star_y;
	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			star_x = stars.getData()[i].getPos().x;
			star_y = stars.getData()[i].getPos().y;
			mvaddch(star_y, star_x, ' ');
		}
	}

	for (size_t i = 0; i < bullets.getCount(); i++) {
		if (bullets.getData()[i].isActive()) {
			star_x = bullets.getData()[i].getPos().x;
			star_y = bullets.getData()[i].getPos().y;
			mvaddch(star_y, star_x, ' ');
		}
	}
}

void	Game::print() {
	int star_x, star_y;
	for (size_t i = 0; i < stars.getCount(); i++) {
		if (stars.getData()[i].isActive()) {
			star_x = stars.getData()[i].getPos().x;
			star_y = stars.getData()[i].getPos().y;
			mvaddch(star_y, star_x, '@');
		}
	}
	for (size_t i = 0; i < bullets.getCount(); i++) {
		if (bullets.getData()[i].isActive()) {
			star_x = bullets.getData()[i].getPos().x;
			star_y = bullets.getData()[i].getPos().y;
			mvaddch(star_y, star_x, '-');
		}
	}
}

void Game::controlHandler(int maxx, int maxy) {
	int in_char;
	in_char = wgetch(main_window);

	mvaddch(p1.pos.y, p1.pos.x, ' ');

	if (in_char == 'q' || in_char == 27)
	{
		endwin();
		std::exit(0);
	}
	else if (in_char == ' ') {
		bullets.activate(p1.pos.x, p1.pos.y);
	}
	else if ((in_char == KEY_UP || in_char == 'w') && p1.pos.y > 1)
		p1.pos.y--;
	else if ((in_char == KEY_DOWN || in_char == 's') && p1.pos.y < maxy - 2)
		p1.pos.y++;
	else if ((in_char == KEY_LEFT || in_char == 'a') && p1.pos.x > 1)
		p1.pos.x--;
	else if ((in_char == KEY_RIGHT || in_char == 'd') && p1.pos.x < maxx - 2)
		p1.pos.x++;
}

void	Game::run() {

	int maxy, maxx;
	int star_x, star_y;
	getmaxyx(main_window, maxy, maxx);
	// init rect with 0,0 origin and width and height
	Rect game_area(maxy, maxx);
	stars.setBounds(game_area);
	bullets.setBounds(game_area);
	
	while(42){
 	// Collision detection here
	if (collisionHandler() == true)
		gameOver();

	shootStar();
	trailCleaner(); // Cleaning up trails for chars

	stars.update();
	bullets.update();

	print();

	controlHandler(maxx, maxy);

	mvaddch(p1.pos.y, p1.pos.x, p1.disp_char);

	usleep(42000); // 42ms
			
	refresh();
	}
}

