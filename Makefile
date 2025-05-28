##
## EPITECH PROJECT, 2025
## Plazza
## File description:
## Main Makefile
##

# Executable names
NAME = plazza

TESTS_NAME = unit_tests.out

# Folders name
SRCDIR = ./src/
TESTS = ./tests/

# Sources
MAIN = $(SRCDIR)main.cpp
SRC =	\
		$(SRCDIR)OptionParser.cpp	\
		$(SRCDIR)CommandInterpreter.cpp	\

TESTS_SRC =	\


# Headers folder
INCLUDES = ./include/

SRC_INCLUDE = ./src/

# GCC Flags
ERROR = -Werror -Wall -Wextra -Wshadow

# Compilation Flags
CFLAGS += $(ERROR) -I$(INCLUDES) -I$(SRC_INCLUDE)	\
			-g -std=c++23 -fPIE -fPIC -fno-gnu-unique -lpthread

# Pre Compilation
CC := g++

OBJ = $(SRC:.cpp=.o)

DEP	=	$(SRC:.cpp=.d)	\
		$(MAIN:.cpp=.d)

# Test Compilation Flags
UNIT_FLAGS = $(FLAGS) -lcriterion --coverage -pie

all: $(NAME)

$(NAME): $(OBJ) $(MAIN:.cpp=.o)
	$(CC) -o $(NAME) $(OBJ) $(MAIN:.cpp=.o) $(CFLAGS)

$(TESTS)%.o: $(TESTS)%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

-include $(DEP)
%.o: %.cpp
	$(CC) -c $< -o $@ -MMD -MF $*.d -MT $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(MAIN:.cpp=.o)
	rm -f $(TESTS_SRC:.cpp=.o)
	rm -f $(DEP)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTS_NAME)

re: fclean all

re_clean: fclean all clean

unit_tests: $(OBJ) $(TESTS_SRC:.cpp=.o)
	$(CC) -o $(TESTS_NAME) $(OBJ) $(TESTS_SRC:.cpp=.o) $(UNIT_FLAGS)

tests_run: unit_tests
	./$(TESTS_NAME) --verbose

coverage: tests_run
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch

.PHONY: all clean \
	fclean re \
	tests_run unit_tests coverage
