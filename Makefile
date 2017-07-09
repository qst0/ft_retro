NAME		= ft_retro

JUNK		= ._rush00.en.pdf

CXX			= g++
CXXFLAGS	= -std=c++98 -Wall -Wextra -Werror -Wno-unused

FILENAMES	= main Game GameObject GameObjectField Rect Player Vec2i Vec2ui Bullets
SRC			= $(addsuffix .cpp, $(FILENAMES))

INCLUDE		= -I.
LINK		= -lncurses

.PHONY: all clean fclean re

all: $(NAME)

test: $(NAME)
	./$(NAME)

$(NAME): $(SRC)
	@$(CXX) $(CXXFLAGS) $(LINK) $(INCLUDE) $^ -o $@
	@echo "\033[32m$(NAME) compiled\033[0m"

clean:
	@rm -f $(JUNK)
	@rm -f $(NAME)
	@echo "\033[31;1mremoved $(NAME)\033[0m"

fclean: clean

re: fclean all
