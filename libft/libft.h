/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:13 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/12 11:39:03 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

int		ft_atoi(const char *nptr, int *error_flag);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

int		ft_isalnum(char c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(char c);

int		ft_isprint(int c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memset(void *b, int c, size_t len);

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *s, int fd);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t	ft_strlen(const char *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char	*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);

int		ft_toupper(int c);

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

void	ft_lstadd_back(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstdelon(t_list *lst, void (*del)(void *));

t_list	*ft_lstlast(t_list *lst);

void	ft_lstiter(t_list *lst, void (*f)(void *));

int		ft_print_dec(int n);

int		ft_print_hex_lower(unsigned int val);

int		ft_print_hex_upper(unsigned int val);

int		ft_print_pointer(void *val);

int		ft_print_str(char *s);

int		ft_print_undec(unsigned int num);

int		ft_printf(const char *fixed_arg, ...);

int		ft_strlen_pf(char *s);

char	*get_next_line(int fd);

char	*ft_str_chr(const char *s, int c);

char	*ft_str_dup(char *str);

void	free_double(void **arr);

int		ft_strcmp(char *s1, char *s2);

char	*ft_strconcat(char *path, char *cmd);

char	*ft_strcpy(char *cmd_path, char *cmd, int j);

char	*ft_strcat(char *s1, char *s2);

int		count_arr_size(char **arr, int arr_count);

char	*join_strings_with_spaces(int size, int count, char **arr);

char	*update_str(char *str, char c);

char	*ft_strjoin_free(char *s1, char *s2);

#endif