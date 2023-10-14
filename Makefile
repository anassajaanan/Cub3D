NAME      = cub3d

# Define ANSI color codes
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BOLD =	\033[1m
RESET = \033[0m

# Define emojis
ROCKET = 🚀
TRASH = 🗑️
CLEAN = 🧹

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -Imlx
LIB_FLAGS = -L./lib/ -lft -L./mlx -lmlx -framework OpenGL -framework AppKit
INCLUDES  = -I./include -I./lib/include -I./mlx
AR        = ar -rcs
RM        = rm -fr

SRCS_DIR  = srcs
OBJS_DIR  = objs

# List of source files
SRCS      = main.c
SRCS      := $(addprefix $(SRCS_DIR)/, $(SRCS))

# List of object files
OBJS      = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# Default rule
all: $(NAME)


$(NAME):	$(OBJS)
	@echo "$(YELLOW)Building $(NAME) $(ROCKET)$(RESET)"
	@echo "   $(YELLOW)🎯 libft.a $(RESET)"
	@make -C ./lib
	@echo "   $(YELLOW)🎯 libmlx.a $(RESET)"
	@echo "      $(BOLD)🔨 Building libmlx.a ...$(RESET_COLOR)"
	@make -s -C ./mlx
	@echo "      $(BOLD)✅ libmlx.a created successfully!$(RESET_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) built successfully!$(RESET)"



# Rule to build object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the objs directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@echo "$(YELLOW)Cleaning project $(CLEAN)$(RESET)"
	@make clean -C ./lib
	@make clean -C ./mlx
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)Project cleaned!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Force cleaning project $(TRASH)$(RESET)"
	@make fclean -C ./lib
	@$(RM) $(NAME)
	@echo "$(GREEN)Project forcefully cleaned!$(RESET)"

# Re rule
re: fclean all

.PHONY: all clean fclean re

