NAME = ft_retro

JUNK = ._rush00.en.pdf

CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -Wno-unused

FILENAMES = main.cpp Game.cpp GameObject.cpp

INCLUDE = -I.
LINK = -lncurses

.PHONY: all clean fclean re

all: $(NAME)

test: $(NAME)
	./$(NAME)

$(NAME): $(FILENAMES)
	$(CXX) $(CXXFLAGS) $(LINK) $(INCLUDE) $^ -o $@

clean:
	@rm -f $(JUNK)
	@rm -f $(NAME)
	@echo "removed $(NAME)"

fclean: clean

re: fclean all
