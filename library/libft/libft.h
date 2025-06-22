/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:04:13 by skhastag          #+#    #+#             */
/*   Updated: 2024/05/22 01:34:57 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int ch);
int		ft_toupper(int ch);
int		ft_isdigit(int ch);
int		ft_tolower(int ch);
int		ft_isalnum(int ch);
int		ft_isascii(int ch);
int		ft_isprint(int ch);
int		ft_check_space(int ch);

int		ft_strncmp(char const *s1, char const *s2, size_t n);
char	*ft_strchr(char const *str, int ch);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *src, const char *to_find, size_t size);
char	*ft_strrchr(char const *str, int ch);

int		ft_memcmp(const void *s1, const void *s2, size_t len);
void	ft_bzero(void *s, size_t len);
void	*ft_memchr(void const *str, int c, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t count);
void	*ft_memset(void *str, int c, size_t len);
void	*ft_memmove( void *dest, const void *src, size_t count );
int		ft_atoi(char const *str);
char	*ft_strdup(char *src);
void	*ft_calloc(size_t num, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
