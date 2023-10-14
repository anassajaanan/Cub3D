/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:47:13 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:09:24 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

struct							s_queue_node_char
{
	char						val;
	struct s_queue_node_char	*next;
};

typedef struct s_queue_char
{
	struct s_queue_node_char	*front;
	struct s_queue_node_char	*rear;
}								t_queue_char;

typedef struct s_list
{
	void						*content;
	struct s_list				*next;
}								t_list;

/* #================== LIBFT: Part 1 ==================# */
int								ft_atoi(const char *str);
long long						ft_atoll(const char *str, int *over_under_flow);
void							ft_bzero(void *str, size_t num);
void							*ft_calloc(size_t nbr_elmts, size_t size);
int								ft_isalpha(int c);
int								ft_isascii(int c);
int								ft_isdigit(int c);
int								ft_isprint(int c);
int								ft_isalnum(int c);
void							*ft_memchr(const void *str, int c, size_t num);
int								ft_memcmp(const void *ptr1, const void *ptr2,
									size_t num);
void							*ft_memcpy(void *dest, const void *src,
									size_t n);
void							*ft_memmove(void *dest, const void *src,
									size_t num);
void							*ft_memset(void *b, int c, size_t len);
char							*ft_strchr(const char *str, int c);
char							*ft_strdup(const char *str);
size_t							ft_strlcat(char *dest, const char *src,
									size_t destsize);
size_t							ft_strlcpy(char *dest, const char *src,
									size_t size);
size_t							ft_strlen(const char *str);
int								ft_strcmp(const char *s1, const char *s2);
int								ft_strncmp(const char *str1, const char *str2,
									size_t n);
char							*ft_strnstr(const char *str, const char *sub,
									size_t len);
char							*ft_strrchr(const char *str, int c);
int								ft_tolower(int c);
int								ft_toupper(int c);

/* #================== LIBFT: Part 2 ==================# */
char							*ft_itoa(int n);
void							ft_putchar_fd(char c, int fd);
void							ft_putendl_fd(char *s, int fd);
void							ft_putnbr_fd(int n, int fd);
void							ft_putstr_fd(char *s, int fd);
char							**ft_split(const char *str, char sep);
char							*ft_strjoin(const char *s1, const char *s2);
char							*ft_strmapi(const char *str,
									char (*f)(unsigned int, char));
void							ft_striteri(char *str, void (*f)(unsigned int,
										char *));
char							*ft_strtrim(const char *s1, const char *set);
char							*ft_substr(const char *str, unsigned int start,
									size_t len);

/* #================== LIBFT: BONUS ==================# */
int								ft_lstsize(t_list *head);
t_list							*ft_lstnew(void *content);
t_list							*ft_lstlast(t_list *head);
void							ft_lstadd_front(t_list **head, t_list *new);
void							ft_lstadd_back(t_list **head, t_list *new);
void							ft_lstdelone(t_list *node, void (*del)(void *));
void							ft_lstclear(t_list **head, void (*del)(void *));
void							ft_lstiter(t_list *head, void (*f)(void *));
t_list							*ft_lstmap(t_list *lst, void *(*f)(void *),
									void (*del)(void *));

/* #================== FT_PRINTF ===================#= */
void							ft_putchar(char c, int *counter);
void							ft_puthex(uintptr_t n, char case_type,
									int *counter);
void							ft_putnbr(int n, int *counter);
void							ft_putptr(void *ptr, int *counter);
void							ft_putstr(char *str, int *counter);
void							ft_putunbr(unsigned int n, int *counter);
void							handle_format_specifier(va_list args, char c,
									int *counter);
int								ft_printf(const char *format, ...);

/* #================== FT_PRINTF_FD ==================# */
void							putchar_fd(int fd, char c, int *counter);
void							puthex_fd(int fd, uintptr_t n, char case_type,
									int *counter);
void							putnbr_fd(int fd, int n, int *counter);
void							putptr_fd(int fd, void *ptr, int *counter);
void							putstr_fd(int fd, char *str, int *counter);
void							putunbr_fd(int fd, unsigned int n,
									int *counter);
void							handle_format_specifier_fd(int fd, va_list args,
									char c, int *counter);
int								ft_printf_fd(int fd, const char *format, ...);

/* #================ GET_NEXT_LINE ==================# */
/* QUEUE_CHAR */
void							init_queue_char(t_queue_char *q);
void							enqueue_char(t_queue_char *q, char c);
void							enqueue_str(t_queue_char *q, char *str);
char							dequeue_char(t_queue_char *q);
char							*queue_char_to_str(t_queue_char *q);

/* GET_NEXT_LINE */
int								contains_newline(t_queue_char *q);
char							*get_line(t_queue_char *q);
char							*get_last_line(t_queue_char *q);
char							*handle_bytes(ssize_t bytes, t_queue_char *q,
									char *buffer, int *fd);
char							*get_next_line(int fd);

#endif // LIBFT_H
