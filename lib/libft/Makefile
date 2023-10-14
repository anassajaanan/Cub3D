NAME			=	libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar -rcs

SRCS_LIBFT		=	ft_atoi.c ft_atoll.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
					ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c \
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
					ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
					ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

SRCS_PRINTF		=	ft_printf.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putptr.c ft_putstr.c \
					ft_putunbr.c

SRCS_PRINTF_FD	=	ft_printf_fd.c putchar_fd.c puthex_fd.c putnbr_fd.c putptr_fd.c putstr_fd.c \
					putunbr_fd.c

SRCS_GNL		=	get_next_line.c get_next_line_utils.c

SRCS_DIR		=	srcs
OBJ_DIR			=	objs

OBJS_LIBFT		=	$(addprefix $(OBJ_DIR)/srcs/libft/, $(SRCS_LIBFT:.c=.o))
OBJS_PRINTF		=	$(addprefix $(OBJ_DIR)/srcs/ft_printf/, $(SRCS_PRINTF:.c=.o))
OBJS_PRINTF_FD	=	$(addprefix $(OBJ_DIR)/srcs/ft_printf_fd/, $(SRCS_PRINTF_FD:.c=.o))
OBJS_GNL		=	$(addprefix $(OBJ_DIR)/srcs/get_next_line/, $(SRCS_GNL:.c=.o))

RESET_COLOR		=	\033[0m
BOLD			=	\033[1m
RED				=	\033[91m
GREEN			=	\033[92m

all: $(NAME)

$(NAME): $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_PRINTF_FD) $(OBJS_GNL)
	@echo "$(BOLD)🔨 Building $(NAME) ...$(RESET_COLOR)"
	@$(AR) $(NAME) $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_PRINTF_FD) $(OBJS_GNL)
	@echo "$(BOLD)$(GREEN)✅ $(NAME) created successfully!$(RESET_COLOR)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BOLD)🧹 Cleaning object files ...$(RESET_COLOR)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(BOLD)🗑️  Cleaning $(NAME) ...$(RESET_COLOR)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re