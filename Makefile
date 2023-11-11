# Target and File Variables
NAME = cub3D
SRCS_DIR = srcs
OBJS_DIR = objs

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	SRCS =	main.c \
			queue.c \
			free.c \
			parsing.c \
			parsing_validation.c \
			parsing_helpers.c \
			map_validation.c \
			map.c
else
	SRCS =	main.c \
			queue.c \
			free.c \
			parsing.c \
			parsing_validation.c \
			parsing_helpers.c \
			map_validation.c \
			map.c \
			init.c \
			init_images.c \
			point.c \
			line.c \
			raycasting.c \
			ray_intersection.c \
			rendering.c
			hooks.c \
			player_mouvements.c \
			player_actions.c
endif
		
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

ifeq ($(UNAME_S), Linux)
	CC = gcc
	CFLAGS = -Wall -Wextra -Werror -g3
	LIB_FLAGS = -L./lib/libft -lft
	INCLUDES = -I./include -I./lib/libft/include
else
	CC = cc
	CFLAGS = -g3 -Wall -Wextra -Werror -Imlx -fsanitize=address
	LIB_FLAGS = -L./lib/libft -lft -L./lib/mlx -lmlx -framework OpenGL -framework AppKit
	INCLUDES = -I./include -I./lib/libft/include -I./lib/mlx
endif

AR = ar -rcs
RM = rm -fr

# ANSI Color Codes
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BOLD = \033[1m
CYAN = \033[1;36m
MAGENTA = \033[1;35m
RESET = \033[0m

# Emojis
ROCKET = 🚀
TRASH = 🗑️
CLEAN = 🧹

# Default Target
all: $(NAME)

# Build Target
$(NAME): $(OBJS)
	@echo "$(YELLOW)Building $(NAME) $(ROCKET)$(RESET)"
	@echo "   $(BOLD)$(CYAN)🎯 libft.a $(RESET)"
	@make -C ./lib/libft
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		@echo "\n   $(BOLD)$(CYAN)⛳️ libmlx.a $(RESET)"; \
		@echo "      $(BOLD)⚙️  Building libmlx.a ...$(RESET)"; \
		@make -s -C ./lib/mlx; \
	fi
	@sleep 3
	@echo "      $(BOLD)✅ libmlx.a created successfully!$(RESET)"
	@echo "\n   ⌛ Compiling $(NAME) ..." && sleep 1
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB_FLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D Built Successfully!$(RESET) 🎉"

# Rule to build object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the objs directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Cleaning Targets
clean:
	@echo "$(YELLOW)Cleaning project $(RESET)"
	@echo "\n   $(BOLD)🚿 Cleaning libft.a ...$(RESET_COLOR)"
	@make clean -C ./lib/libft
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		echo "   $(BOLD)🧹 Cleaning libmlx.a ...$(RESET_COLOR)"; \
		make clean -C ./lib/mlx; \
	fi
	@echo "   $(BOLD)🗑️  Cleaning $(NAME) ...$(RESET_COLOR)"
	@$(RM) $(OBJS_DIR)
	@echo "\n$(GREEN)Project cleaned! ✨$(RESET)"

fclean: clean
	@echo "\n$(YELLOW)Force cleaning project$(RESET)"
	@echo "\n   $(BOLD)$(RED)🗑️ Force cleaning libft.a ...$(RESET)"
	@make fclean -C ./lib/libft
	@echo "   $(BOLD)$(RED)🗑️ Force cleaning $(NAME) ...$(RESET)"
	@$(RM) $(NAME)
	@echo "\n$(GREEN)Project forcefully cleaned! ✨$(RESET)"

# Restarting Target
re:
	@echo "$(BOLD)$(MAGENTA)Force cleaning $(NAME) ♻️$(RESET)"
	@make -s fclean > /dev/null
	@make all

.PHONY: all clean fclean re
