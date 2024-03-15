# CC = gcc
# CFLAGS = -Wall -Werror -Wextra -g

# SRC = ./src/minibash.c ./src/check.c ./src/lib/arrdup.c  ./src/lib/arrlen.c  ./src/lib/strjoin.c
# BUILD_DIR = build
# OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

# TARGET = minibash

# all: $(TARGET)

# $(BUILD_DIR):
# 	@mkdir -p $(BUILD_DIR)

# $(OBJ): $(BUILD_DIR) | $(SRC)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) -o $(TARGET) $^

# clean:
# 	rm -rf $(BUILD_DIR) $(TARGET)

# run:
# 	./$(TARGET)

NAME			=		minibash
NAME_TEST		=		test
CC				=		cc
AR				=		ar rcs
RM				=		rm -rf
CFLAGS			=		-Wall -Wextra -Werror -Ofast
SRC				=		$(wildcard src/*/*/*.c) $(wildcard src/*/*.c) $(wildcard src/*.c)
SRC_MAIN		=		main.c	$(SRC)
SRC_TEST		=		test.c	$(SRC)
OBJ				=		$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR			=		obj

RED = \033[31m
GREEN = \033[32m
RESET = \033[0m

$(NAME) : $(OBJ)
	@echo "----- Compiling Minishell -----"
	# ${CC} ${SRC_MAIN} -o ${NAME}  ${LIBFT_LIB} ${GNL_LIB} ${CFLAGS} -lreadline
	${CC} ${SRC_MAIN} -o ${NAME}  ${LIBFT_LIB} ${GNL_LIB} -lreadline
	clear
	@echo "$(RED)╔═══════════════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(GREEN)                              Minishell Compiled!                              $(RED)║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════════════════════════════════════════════════════╝$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	
all: ${NAME}

clean:
	rm -rf $(OBJ_DIR)
	clear

fclean: clean
	rm -f ${NAME}
	rm -f ${NAME_TEST}
	clear
	
re: fclean all

test: build $(OBJ)
	@echo "----- Compiling Test Minishell -----"
	@time -p (	${CC} ${SRC_TEST} -o ${NAME_TEST} ${CFLAGS} -lreadline)
	clear
	@echo "$(RED)╔════════════════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(GREEN)                           Compiling and Running Test ...                       $(RED)║$(RESET)"
	@echo "$(RED)╚════════════════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo
	@echo
	@./test
	@echo

valgrind :
	@valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --error-limit=no --tool=memcheck -s $(NAME_TEST)

.PHONY: all install clean fclean re