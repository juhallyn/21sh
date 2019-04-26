/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 00:32:48 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:34:31 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 32

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

int		get_next_line(int fd, char **line);

void	ft_putchar(unsigned char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putspace(int n);
void	ft_putstr(const char *s);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putendl(const char *s);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	my_printf(const char *str, int fd, ...);
void	ft_putcolor(int nb, ...);
int		ft_strlen(const char *s);

char	*ft_just_alpha(char *str);
char	*ft_just_num(char *str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_isupper(int c);
int		ft_islower(int c);

int		ft_atoi(const char *ntpr);
char	*ft_itoa(int n);

char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strtrim(char const *s);

int		ft_strnequ(char const *s1, char const *s2, size_t n);
void	ft_strclr(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strequ(char const *s1, char const *s2);
int		last_occurence(char *str, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strsub(char const *s, unsigned int start, size_t len);

void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoins(int nb, ...);
char	*ft_strnew(size_t size);

char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);
char	**ft_white_space(char const *s);

void	put_array(char **array);
int		array_len(char **array);
void	array_free(char ***array);
char	**array_dup(char **array);
void	free_tab(char ***tab);

void	ft_strdel(char **as);

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);

void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

#endif
