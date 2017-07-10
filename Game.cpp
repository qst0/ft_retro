#include "Game.hpp"
#include "GameObjectField.hpp"

Game::Game( void ) : main_window(initscr()), p1(13, 5) {  // init() and init player 1 
	cbreak();
	noecho();
	clear();
	refresh();

	tick = 0;
	score = 0;

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
	init_pair(2, 9, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, 8, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_RED);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_BLUE, COLOR_WHITE);
	wbkgd(main_window, COLOR_PAIR(1)); 
	
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	box(main_window, 0, 0);
	attroff(COLOR_PAIR(1));
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
			for (size_t j = 0; j < bullets.getCount(); j++) {
				bull_x = bullets.getData()[j].getPos().x;
				bull_y = bullets.getData()[j].getPos().y;
				//Questionable checking...
				if ((star_x - 1 == bull_x && star_y == bull_y) 
					|| (star_x  == bull_x + 1 && star_y == bull_y)
					|| (star_x  == bull_x && star_y == bull_y)) {
					stars.getData()[i].deactivate();
					if (score < 1000)
						bullets.getData()[j].deactivate();
					// Give score for destroying @'s
					score += 10;
					system("afplay -t 20 ./mp3/explosion.mp3 &");
				}
			}
		}
	}
}

int	Game::gameOver() {
	int in_char;
	int maxy, maxx;
	getmaxyx(main_window, maxy, maxx);

	in_char = wgetch(main_window);
	system("afplay -t 20 ./mp3/ded.mp3 &");
	attron(A_BOLD);
	wbkgd(main_window, COLOR_PAIR(2));
	mvaddch(p1.pos.y, p1.pos.x, 'X');
	while(42) {
		in_char = wgetch(main_window);
		if (in_char == 'q')
			return 0;
		if (in_char == 'r')
			return 1;

		attron(COLOR_PAIR(5));
		std::string text[] = { "GAME OVER", "Press 'q' to quit", "Press 'r' to restart" };
		for (size_t j = 0; j < 3; j++) {
			move((maxy / 2) + j, (maxx / 2) - (text[j].length())) - 2;
			for (size_t i = 0; i < text[j].size(); i++) {
			  addch(text[j][i]);
			  addch(' ');
			  usleep(30000);
			  refresh();
			}
		}
		attroff(COLOR_PAIR(5));
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

	for (size_t i = 0; i < dust.getCount(); i++) {
		if (dust.getData()[i].isActive()) {
			star_x = dust.getData()[i].getPos().x;
			star_y = dust.getData()[i].getPos().y;
			if (star_x != p1.pos.x || star_y != p1.pos.y)
			 mvaddch(star_y, star_x, ' ');
		}
	}

	for (size_t i = 0; i < bullets.getCount(); i++) {
		if (bullets.getData()[i].isActive()) {
			star_x = bullets.getData()[i].getPos().x;
			star_y = bullets.getData()[i].getPos().y;
			if (star_x != p1.pos.x || star_y != p1.pos.y)
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
			attron(COLOR_PAIR(6));
			mvaddch(star_y, star_x, '@');
			attroff(COLOR_PAIR(6));
		}
	}
	for (size_t i = 0; i < dust.getCount(); i++) {
		if (dust.getData()[i].isActive()) {
			star_x = dust.getData()[i].getPos().x;
			star_y = dust.getData()[i].getPos().y;

			if (star_x != p1.pos.x || star_y != p1.pos.y)
			{
				attron(COLOR_PAIR(4));
				mvaddch(star_y, star_x, '.');
				attroff(COLOR_PAIR(4));
			}
		}
	}

	for (size_t i = 0; i < bullets.getCount(); i++) {
		if (bullets.getData()[i].isActive()) {
			star_x = bullets.getData()[i].getPos().x;
			star_y = bullets.getData()[i].getPos().y;
			if (star_x != p1.pos.x || star_y != p1.pos.y)
			{
				attron(COLOR_PAIR(2));
				if (score > 1000)
					mvaddch(star_y, star_x, '=');	
				else
					mvaddch(star_y, star_x, '-');
				attroff(COLOR_PAIR(2));
			}
		}
	}
	//Show score!
	move (1, 2);
	attron(A_BOLD);
	addstr("SCORE: ");
	move (1, 9);
	std::string text = std::to_string(score);
	for (size_t i = 0; i < text.size(); i++) {
		addch(text[i]);
		refresh();
	}
	attroff(A_BOLD);
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
	else if (in_char == ' ')
		bullets.activate(p1.pos.x, p1.pos.y);
	else if ((in_char == KEY_UP || in_char == 'w') && p1.pos.y > 3)
		p1.pos.y--;
	else if ((in_char == KEY_DOWN || in_char == 's') && p1.pos.y < maxy - 2)
		p1.pos.y++;
	else if ((in_char == KEY_LEFT || in_char == 'a') && p1.pos.x > 1)
		p1.pos.x--;
	else if ((in_char == KEY_RIGHT || in_char == 'd') && p1.pos.x < maxx - 2)
		p1.pos.x++;
}

void	Game::init() {
	int maxy, maxx;
	std::string text[] = {
		"WASD or Arrows to Move",
		"Spacebar to Shoot",
		"",
		"It's the year 42-XX...",
		"Twitter has become sentient",
		"Rogue '@' symbols have",
		"started attacking mankind.",
		"Our future depends on you!",
	};

	move(13, 5);

	addch('}');

	std::string const you_text = "You";

	move(11, 4);
	for (size_t i = 0; i < you_text.size(); i++) {
			addch(you_text[i]);
			usleep(30000);
			refresh();
	}

	move(12, 5);
	addch('V');


	getmaxyx(main_window, maxy, maxx);
	for (size_t j = 0; j < 8; j++) {
		move((maxy / 2) - 4 + j, (maxx / 2) - (text[j].length())) - 2;
		for (size_t i = 0; i < text[j].size(); i++) {
			addch(text[j][i]);
			addch(' ');
			usleep(30000);
			refresh();
		}
	}


	return ;
}

int	Game::run() {

	int maxy, maxx;
	int star_x, star_y;
	getmaxyx(main_window, maxy, maxx);
	// init rect with 0,0 origin and width and height
	Rect game_area(4, 0, maxy, maxx);
	stars.setBounds(game_area);
	dust.setBounds(game_area);
	bullets.setBounds(game_area);

	//Rouge @ sign
	stars.getData()[13].activate(32,13);	

	while(42){
	tick++;	
	move(2, 1);
	for (int i = 0; i < maxx - 2; i++)
		addch('-');
 	// Collision detection here
	if (collisionHandler() == true)
		return gameOver();

	shootStar();
	trailCleaner(); // Cleaning up trails for chars

	size_t score_mod;

	if (tick > 42) {
		score_mod = stars.update();
		if (score_mod <= score)
			score -= score_mod;
	}
	
	dust.update();
	bullets.update();

	print();

	controlHandler(maxx, maxy);

	mvaddch(p1.pos.y, p1.pos.x, p1.disp_char);

	// If the player makes it 3000 ticks into the game: WARP SPEED!
	// If the Player makes it to 4000 ticks: 
	if (tick < 3000)
		usleep(42000 - tick * 10); // 42ms
	else if (tick < 5000)
	{
		if (tick == 3000)
		{
			init_pair(2, 9, COLOR_WHITE);
			init_pair(6, COLOR_BLUE, COLOR_WHITE);
			init_pair(4, 8, COLOR_WHITE);
		}

		wbkgd(main_window, COLOR_PAIR(7)); 
		usleep(10001);
	}
	else {
		if (tick == 3000)
		{
			init_pair(2, 0, COLOR_GREEN);
			init_pair(6, COLOR_CYAN, COLOR_GREEN);
			init_pair(4, 9, COLOR_WHITE);
		}

		wbkgd(main_window, COLOR_PAIR(3)); 
		usleep(9001);
	}
	refresh();
	}
	return 0;
}

