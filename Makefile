# Colors / base 16 / Bright
GREEN := \033[32;1m
RESET := \033[0m

# Colors / Perso / Bright
ORANGE = \033[38;5;214m
BLUE = \033[34;1m

# Project settings
NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f
INCLUDE = -I ./include \
          -I ./library/libft/
LINK = -lreadline

# Libft
LIBFT_DIR = ./library/libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

# Source files
SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Targets
all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(INCLUDE) $(LINK)
	@echo "$(GREEN)Minishell ready!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ && printf "$(GREEN)Compiling: $(RESET)$(notdir $<)...\n"

clean:
	@echo "$(ORANGE)Removing object files$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)
	@$(RM) $(NAME).dSYM out*

fclean: clean
	@echo "$(ORANGE)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@make fclean -sC $(LIBFT_DIR)

re: fclean all
	@echo "$(BLUE)Cleaned and rebuilt everything for $(NAME)$(RESET)"

.PHONY: all re clean fclean